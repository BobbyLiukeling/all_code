from django.shortcuts import render
from django.views.generic.base import View
from pure_pagination import Paginator, PageNotAnInteger
import pdb
from django.http import HttpResponse
import json
from django.db.models import Q

# Create your views here.

from .models import CourseOrg,CityDict,Teacher
from .forms import UserAskForm
from courses.models import Course
from operation.models import UserFavorate
from users.models import UserProfile


#分页显示与筛选
class OrgView(View):
    def get(self, request):
        all_orgs = CourseOrg.objects.all()
        all_cities = CityDict.objects.all()

        search_keywords = request.GET.get('keywords', '')
        if search_keywords:
            all_orgs = all_orgs.filter(Q(name__icontains=search_keywords) | Q(desc__icontains=search_keywords) )  # name__icontains contains前面的i表示不区分大小写

        hot_org = all_orgs.order_by("-click_nums")[:3]#按照点击量的前三进行排名,前面加负号是倒叙排列，数字大的在前

        #筛选城市
        city_id = request.GET.get('city', '')
        if city_id:
            all_orgs = all_orgs.filter(city_id=int(city_id))

        category = request.GET.get('ct','')
        if category:
            all_orgs = all_orgs.filter(category=category)

        sort = request.GET.get('sort','')
        if sort:
            if sort == 'students':
                all_orgs = all_orgs.order_by('-students')
            elif sort =='course_nums':
                all_orgs = all_orgs.order_by('-course_nums')

        org_nums = all_orgs.count()#对机构的总量进行统计
        #对课程机构进行分页
        try:
            page = int(request.GET.get('page', 1))
        except PageNotAnInteger:
            page = 1
        paginator = Paginator(all_orgs,3,request=request)#每页显示条数3
        orgs = paginator.page(page)

        return render(request,'org-list.html',{
            "all_orgs":orgs,
            "all_cities":all_cities,
            "org_nums":org_nums,
            'city_id':city_id,#将选中的城市的id传到前端，
            "category":category,
            "hot_org":hot_org,
            'sort':sort,
        })


class AddUserAskViwe(View):
    #用户 添加咨询
    def post(self,request):
        userask_form = UserAskForm(request.POST)
        if userask_form.is_valid():
            user_ask = userask_form.save(commit=True)#直接保存提交
            return HttpResponse(json.dumps({"status":"success","msg":"提交成功"}),content_type='application/json')
        else:
            return HttpResponse(json.dumps({"status":"fail","msg":"信息填写错误，提交失败"}),content_type='application/json')


class OrgHomeView(View):
    def get(self,request,org_id):
        course_org = CourseOrg.objects.get(id = int(org_id))
        fav_nums = UserFavorate.objects.filter(fav_type=2, fav_id=org_id).count()
        course_org.fav_nums = fav_nums
        course_org.click_nums +=1
        course_org.save()

        all_courses = course_org.course_set.all()[:3]#外键反取
        all_teachers = course_org.teacher_set.all()[:2]
        has_fav = False
        if request.user.is_authenticated:
            username = request.user
            user = UserProfile.objects.get(Q(username=username) | Q(email=username))
            user_id = user.id
            if UserFavorate.objects.filter(user_id=user_id, fav_id=course_org.id, fav_type=2):
                has_fav = True
        else:
            username = ''
        name = '首页'

        return render(request,'org-detail-homepage.html',{
            'all_courses':all_courses,
            'all_teachers':all_teachers,
            'course_org':course_org,
            'name': name,
            'username':username,
            'has_fav':has_fav,
        })


class OrgCourseView(View):
    def get(self,request,org_id):
        course_org = CourseOrg.objects.get(id = int(org_id))
        all_courses = course_org.course_set.all()[:3]#外键反取
        has_fav = False
        if request.user.is_authenticated:
            username = request.user
            user = UserProfile.objects.get(Q(username=username) | Q(email=username))
            user_id = user.id
            if UserFavorate.objects.filter(user_id=user_id, fav_id=course_org.id, fav_type=2):
                has_fav = True
        else:
            username = ''
        name = '课程'

        return render(request,'org-detail-course.html',{
            'all_courses':all_courses,
            'course_org': course_org,
            'name':name,
            'username': username,
            'has_fav':has_fav,
        })


class OrgDescView(View):
    def get(self,request,org_id):
        course_org = CourseOrg.objects.get(id = int(org_id))
        name = '描述'
        has_fav = False
        if request.user.is_authenticated:
            username = request.user
            user = UserProfile.objects.get(Q(username=username) | Q(email=username))
            user_id = user.id
            if UserFavorate.objects.filter(user_id=user_id, fav_id=course_org.id, fav_type=2):
                has_fav = True
        else:
            username = ''

        return render(request,'org-detail-desc.html',{
            'course_org': course_org,
            'name':name,
            'username': username,
            'has_fav':has_fav,
        })


class OrgTeacherView(View):
    def get(self,request,org_id):
        course_org = CourseOrg.objects.get(id = int(org_id))
        all_teachers = course_org.teacher_set.all()[:2]#外键反取
        name = '老师'
        has_fav = False
        if request.user.is_authenticated:
            username = request.user
            user = UserProfile.objects.get(Q(username=username) | Q(email=username))
            user_id = user.id
            if UserFavorate.objects.filter(user_id=user_id, fav_id=course_org.id, fav_type=2):
                has_fav = True
        else:
            username = ''

        return render(request,'org-detail-teachers.html',{
            'all_teachers': all_teachers,
            'course_org': course_org,
            'name':name,
            'username': username,
            'has_fav':has_fav,
        })


class AddFavViews(View):
    def post(self,request):
        fav_id = request.POST.get('fav_id',0)
        fav_type = request.POST.get('fav_type',0)
        if not request.user.is_authenticated:#验证用户是否登陆,如果未登录
            return HttpResponse(json.dumps({"status":"fail","msg":"用户未登录"}),content_type='application/json')

        username = request.user
        user = UserProfile.objects.get(Q(username = username)|Q(email = username))
        user_id = user.id
        exit_records = UserFavorate.objects.filter(user_id =user_id ,fav_id = int(fav_id),fav_type =fav_type)
        if exit_records:
            #此收藏已经存在，将会取消之前收藏
            exit_records.delete()
            return HttpResponse(json.dumps({"status": "success", "msg": "收藏"}), content_type='application/json')
        else:
            fav = UserFavorate()
            if int(fav_id)>0 and int(fav_type)>0:
                fav.fav_id = fav_id
                fav.fav_type = fav_type
                fav.user_id = user_id
                fav.save()
                return HttpResponse(json.dumps({"status": "success", "msg": "已收藏"}), content_type='application/json')
            else:
                return HttpResponse(json.dumps({"status": "fail", "msg": "收藏出错"}), content_type='application/json')


class TeacherListView(View):
    def get(self,request):
        teachers = Teacher.objects.all()
        teacher_nums = teachers.count()#对讲师的数量进行计数
        order_teachers = teachers.order_by('-fav_nums')[:5]
        hot_teachers = teachers.order_by('-click_nums')

        search_keywords = request.GET.get('keywords', '')
        if search_keywords:
            teachers = teachers.filter(Q(name__icontains=search_keywords) | Q(points__icontains=search_keywords) | Q(work_company__icontains=search_keywords))  # name__icontains contains前面的i表示不区分大小写

        #排序功能
        sort = request.GET.get('sort','')#从前端取到链接为sort的url
        if sort:#当sort不为空，即，sort的链接被点击了
            if sort == 'hot':
                teachers = teachers.order_by('-click_nums')

        try:
            page = int(request.GET.get('page', 1))
        except PageNotAnInteger:
            page = 1
        paginator = Paginator(teachers,3,request=request)#每页显示条数3
        teachers = paginator.page(page)

        if request.user.is_authenticated:
            username = request.user
        else:
            username = ''

        return render(request,'teachers-list.html',{
        'teachers':teachers,
        'teacher_nums':teacher_nums,
        'order_teachers':order_teachers,
        'username':username,
        'sort':sort,#传到前端，用作显示选中状态
        })

class TeacherDetailView(View):
    def get(self, request,teacher_id):
        '''
        老师被收藏和点击的次数
        '''
        teacher = Teacher.objects.get(id=teacher_id)
        fav_nums = UserFavorate.objects.filter(fav_type = 3,fav_id = teacher_id).count()#当前老师被收藏的次数
        teacher.fav_nums = fav_nums
        teacher.click_nums +=1
        teacher.save()

        courses_org = Course.objects.filter(teacher = teacher)
        org_teachers = Teacher.objects.filter(org=teacher.org).order_by('-click_nums')[:5]#教师所属机构，下面的所有老师

        if request.user.is_authenticated:
            username = request.user
        else:
            username = ''

        teacher_has_fav = False
        org_has_fav = False
        if UserFavorate.objects.filter(user = request.user,fav_type = 3, fav_id = teacher.id):#讲师已收藏
            teacher_has_fav = True
        if UserFavorate.objects.filter(user = request.user,fav_type = 2, fav_id = teacher.org.id):#机构已收藏
            org_has_fav = True

        return render(request, 'teacher-detail.html', {
            'username':username,
            'teacher':teacher,
            'courses':courses_org,
            'org_teachers':org_teachers,
            'teacher_has_fav':teacher_has_fav,
            'org_has_fav':org_has_fav,
        })
