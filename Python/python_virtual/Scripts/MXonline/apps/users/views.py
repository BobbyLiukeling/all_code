from django.shortcuts import render
from django.contrib.auth import authenticate,login as Lo,logout as Logout#局部方法和全局方法重名解决办法
from django.contrib.auth.backends import ModelBackend
from django.http import HttpResponse,HttpResponseRedirect
from django.db.models import Q
from django.views.generic.base import View
from django.contrib.auth.hashers import make_password
from django.core.mail import send_mail
from django.urls import reverse
from pure_pagination import Paginator, PageNotAnInteger
import pdb
import random

import json


from utils.mixin_utils import LoginRequiredMixin#验证是否登陆
from operation.models import UserCourse,UserFavorate,UserMessage
from courses.models import Course
from organization.models import CourseOrg,Teacher


# from MXonline.settings import EMAIL_FROM
from .models import UserProfile,EmailVerifyRecord,Banner
from .forms import LoginForm, RegisterForm,ForgetForm,ModifyPwdForm,UploadImgForm,UserInfoForm
from .email_send import send_register_email

code = str(random.randint(100000, 999999))
active_username = ''

class CustomBackend(ModelBackend):#邮箱，用户名同时登陆
    def authenticate(self, request, username=None, password=None, **kwargs):
        try:
            user = UserProfile.objects.get(Q(username = username)|Q(email = username))
            if user.check_password(password):
                return user
        except Exception as e:
            return None


class LoginView(View):
    def get(self,request):
        return render(request, "login.html", {})

    def post(self,request):#如果字段有错
        login_form = LoginForm(request.POST)
        if login_form.is_valid():
            user_name = request.POST.get("username", " ")
            pass_word = request.POST.get("password", " ")
            user = authenticate(username=user_name, password=pass_word)#对用户名和密码验证，会自动和数据库中断内容进行对比
            if user is not None:
                if user.is_active:
                    Lo(request, user)  # 局部方法和全局方法重名解决办法
                    return HttpResponseRedirect(reverse('index'))
                else:
                    return render(request, "login.html", {'msg': "用户未激活"})
            else:#用户名或密码有误
                return render(request, "login.html", {'msg': "用户名或密码错误"})
        else:#如果有字段为空
            return render(request, "login.html", {'msg': "用户名或密码有误","login_form":login_form})


class LogoutView(View):
    def get(self,request):
        Logout(request)#退出登陆
        '''
        重定向到首页
        HttpResponseRedirect 是网页重定向
        reverse（from django.urls import reverse）将网页名称反解成网页地址
        '''
        return HttpResponseRedirect(reverse('index'))



class ActiveView(View):
    def get(self, request,active_code):
        all_records = EmailVerifyRecord.objects.filter(code = active_code)
        if all_records:
            for record in all_records:
                email = record.email
                user = UserProfile.objects.get(email = email)
                user.is_active = True
                user.save()
        else:
            return render(request,'active_fail.html')
        return render(request,"login.html")


class RegisterView(View):
    def get(self,request):
        register_form = RegisterForm()
        # pdb.set_trace()
        return render(request,"register.html", {'register_form':register_form})
        #return render(request, "register.html")

    def post(self,request):
        register_form = RegisterForm(request.POST)
        if register_form.is_valid():#直接过滤掉验证码（如果验证码正确的话），
            user_name = request.POST.get("email", " ")
            if UserProfile.objects.filter(email=user_name):
                return render(request,'register.html',{'msg': "用户已存在","register_form": register_form})
            pass_word = request.POST.get("password", " ")
            user_profile = UserProfile()
            user_profile.email = user_name
            user_profile.username = user_name
            user_profile.password = make_password(pass_word)#j将密码加密
            user_profile.is_active = 0#表明用户还未激活
            user_profile.save()

            #向用户发送消息
            user_message = UserMessage()
            user_message.user = user_profile.id
            user_message.message = '欢迎注册'
            user_message.save()


            send_register_email(user_name,"register")
            return render(request, "login.html")  # 跳转到输入邮箱验证码页面
        else:
            return render(request, "register.html", {"register_form": register_form})




# Create your views here.
# def login(request):
#     if request.method == "POST":
#         user_name = request.POST.get("username"," ")
#         pass_word = request.POST.get("password"," ")
#         user = authenticate(username = user_name,password = pass_word)
#         if user is not None:
#             Lo(request,user)#局部方法和全局方法重名解决办法
#             return render(request, "index.html", {'name':user_name})
#         else :
#             return render(request,"login.html",{'msg':"用户名或密码错误"})
#     elif request.method == "GET":
#         return render(request,"login.html",{})
#


class ForgetPwdView(View):
    def get(self,request):
        forget_form = ForgetForm()
        return render(request,'forgetpwd.html',{"forget_form":forget_form})

    def post(self,request):
        forget_form = ForgetForm(request.POST)
        if forget_form.is_valid():
            email = request.POST.get("email",'')
            send_register_email(email, 'forget')
            return render(request,'email_send.html')
        else:
            return render(request,'forgetpwd.html',{"forget_form":forget_form})


class ResetView(View):
    def get(self, request,active_code):
        all_records = EmailVerifyRecord.objects.filter(code = active_code)
        if all_records:
            for record in all_records:
                email = record.email
                return render(request,'password_reset.html',{"email":email})
        else:
            return render(request,'active_fail.html')
        return render(request,"login.html")


class ModifyPwdView(View):
    def post(self,request):
        modify_form = ModifyPwdForm(request.POST)
        if modify_form.is_valid():
            pwd1 = request.POST.get('password1','')
            pwd2 = request.POST.get('password2','')
            email = request.POST.get('email','')
            if pwd1 != pwd2:
                return render(request,'password_reset.html',{"email":email,'msg':"两次密码不一致，请重新输入"})
            else:
                user = UserProfile.objects.get(email = email)#取出相应数据
                s=user.email
                user.password = make_password(pwd1)
                user.save()
                return render(request,'login.html')
        else:
            email = request.POST.get('email', '')
            return render(request,"password_reset.html",{"email":email,"msg":"验证未通过"})


class UserInfoView(LoginRequiredMixin, View):#验证是否登陆
    def get(self,request):
        return render(request,'usercenter-info.html',{
        })


class UploadImgView(LoginRequiredMixin,View):
    def post(self,request):
        # image_form = UploadImgForm(request.POST,request.FILES)#image是文件类型，不是字段所以后面要加上request.FILES
        # if image_form.is_valid():
        #     '''
        #     当前端上传图片的时候，如果前端拿到图片，那么clrarned_data里面变回存放前端验证通过的数据
        #     而且数据的字段名称与前端的标签的属性名称一致
        #     '''
        #     img = image_form.cleaned_data['image']  #
        #     request.user.image = img
        #     request.user.save()

        '''
           UploadImgForm(request.POST)是前端form传递到 后台的数据
            request.FILES 是签单传递的数据类型为file，不再是字段了（默认是字段）
            instance=request.user
        '''
        image_form = UploadImgForm(request.POST,request.FILES,instance=request.user)
        if image_form.is_valid():
            image_form.save()
            return HttpResponse(json.dumps('{"status":"success"}'),content_type='application/json')
        else:
            return HttpResponse(json.dumps('{"status":"fail"}'), content_type='application/json')


class ResetPwdView(View):
    def post(self,request):
        modify_form = ModifyPwdForm(request.POST)
        if modify_form.is_valid():
            pwd1 = request.POST.get('password1','')
            pwd2 = request.POST.get('password2','')
            if pwd1 != pwd2:
                return HttpResponse(json.dumps('{"status":"fail","msg":"两次密码不一致，请重新输入"}'),content_type='application/json')
            else:
                user = request.user
                user.password = make_password(pwd1)
                user.save()
                return HttpResponse(json.dumps('{"status":"success"}'), content_type='application/json')
        else:
            return HttpResponse(json.dumps(modify_form.errors),content_type='application/json')


class ResetEmailView(View):

    '''
    发送邮箱验证码
    '''
    def get(self,request):
        email = request.GET.get('email','')
        if UserProfile.objects.filter(email= email):
            return HttpResponse(json.dumps('{"email":"邮箱已存在"}'),content_type='application/json')
        send_register_email(email,'update')
        return HttpResponse(json.dumps('{"status":"success"}'),content_type='application/json')


class EmailVerifyView(LoginRequiredMixin, View):
    def post(self, request):
        email = request.POST.get('email','')
        code = request.POST.get('code','')
        if EmailVerifyRecord.objects.filter(email = email,code=code, send_type = 'update'):#从数据库查询到当时发送邮件所保存的信息
            user = request.user
            user.email = email
            user.save()
            return HttpResponse(json.dumps('{"status":"success"}'),content_type='application/json')
        else:
            return HttpResponse(json.dumps('{"email":"验证码出错"}'), content_type='application/json')


class ResetUserInfoView(LoginRequiredMixin,View):
    def post(self,request):
        '''
        因为UserInfoForm是继承ModelForm的form，所以user_info可以像model那样直接保存前端的数据到数据库
        '''
        user_info = UserInfoForm(request.POST,instance=request.user)#后面的request.user很重要，不知道为什么
        if user_info.is_valid():
            user_info.save()
            return HttpResponse(json.dumps('{"status":"success"}'),content_type='application/json')
        else:
            return HttpResponse(json.dumps(user_info.errors),content_type='application/json')


class UserCourseView(LoginRequiredMixin,View):
    def get(self,request):
        usercourses = UserCourse.objects.filter(user = request.user)
        return render(request,'usercenter-mycourse.html',{
            'usercourses':usercourses,
        })

class UserFavCourseView(LoginRequiredMixin,View):
    def get(self,request):
        fav_courses = UserFavorate.objects.filter(fav_type = 1,user = request.user)
        msg = ''
        courses = []
        if fav_courses:
            for fav in fav_courses:
                course = Course.objects.get(id = fav.fav_id)
                courses.append(course)
            return render(request, 'usercenter-fav-course.html', {
                'courses': courses,
                'msg':msg
            })
        else:
            msg = '该同学没有收藏任何课程'
            return render(request,'usercenter-fav-course.html',{
                'msg':msg
            })


class UserFavOrgView(LoginRequiredMixin,View):
    def get(self,request):
        fav_orgs = UserFavorate.objects.filter(fav_type=2, user=request.user)
        msg = ''
        orgs = []
        if fav_orgs:
            for fav in fav_orgs:
                org = CourseOrg.objects.get(id=fav.fav_id)
                orgs.append(org)
            return render(request, 'usercenter-fav-org.html', {
                'orgs': orgs,
                'msg': msg
            })
        else:
            msg = '该同学没有收藏任何课程机构'
            return render(request, 'usercenter-fav-org.html', {
                'msg': msg
            })


class UserFavTeacherView(LoginRequiredMixin,View):
    def get(self,request):
        fav_teachers = UserFavorate.objects.filter(fav_type=3, user=request.user)
        msg = ''
        teachers = []
        if fav_teachers:
            for fav in fav_teachers:
                teacher = Teacher.objects.get(id=fav.fav_id)
                teachers.append(teacher)
            return render(request, 'usercenter-fav-teacher.html', {
                'teachers': teachers,
                'msg': msg
            })
        else:
            msg = '该同学没有收藏任何老师'
            return render(request, 'usercenter-fav-teacher.html', {
                'msg': msg
            })


class UserMsgView(LoginRequiredMixin,View):
    def get(self,request):
        all_messages = UserMessage.objects.filter(user = request.user.id)
        all_unread = UserMessage.objects.filter(user = request.user.id,has_read = False)
        for message in all_unread:
            message.has_read = True
            message.save()

        try:
            page = int(request.GET.get('page', 1))#这里要做一下int转换,这里的request.GET.get('page', 1)中的page是Django在分页时自动生成的
        except PageNotAnInteger:
            page = 1
        paginator = Paginator(all_messages,3,request=request)#每页显示条数3
        messages = paginator.page(page)

        return render(request,'usercenter-message.html',{
            'messages':messages
        })


class IndexView(View):
    def get(self,request):
        course_banners = all_courses = Course.objects.all().order_by('-click_nums')[:2]
        all_courses = Course.objects.all().order_by('-click_nums')[:6]
        all_orgs = CourseOrg.objects.all().order_by('-click_nums')[:15]
        banners = Banner.objects.all().order_by('index')[:5]#只要五张
        # pdb.set_trace()
        return render(request,'index.html',{
            'all_courses':all_courses,
            'all_orgs':all_orgs,
            'banners':banners,
            'course_banners':course_banners
        })


#全局404处理函数
def page_not_found(request):
    from django.shortcuts import render_to_response
    response = render_to_response('404.html',{})
    response.status_code = 404
    return response


#500处理页面
def page_error(request):
    from django.shortcuts import render_to_response
    response = render_to_response('500.html',{})
    response.status_code = 500
    return response

#403处理页面
def page_403(request):
    from django.shortcuts import render_to_response
    response = render_to_response('403.html',{})
    response.status_code = 403
    return response



from .forms import TestForm
from captcha.models import CaptchaStore
from captcha.helpers import captcha_image_url
class test(View):
    def get(self,request):
        hashkey = CaptchaStore.generate_key()
        image_url = captcha_image_url(hashkey)
        # test_form = TestForm()     # Python内置了一个locals()函数，它返回当前所有的本地变量字典
        return render(request, 'test.html', {'key':hashkey,'image':image_url})








