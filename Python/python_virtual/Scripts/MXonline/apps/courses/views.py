from django.shortcuts import render
from django.views.generic.base import View
from pure_pagination import Paginator, PageNotAnInteger
import pdb
from django.db.models import Q
from django.http import HttpResponse
# Create your views here.

from .models import Course,CourseResource,Video
from users.models import UserProfile
from operation.models import UserFavorate,CourseComment,UserCourse
from utils.mixin_utils import LoginRequiredMixin


class CourseList(View):
    def get(self,request):
        all_courses = Course.objects.all().order_by("-add_time")
        hot_courses = Course.objects.all().order_by("-click_nums")[:3]

        #完成搜索功能
        search_keywords = request.GET.get('keywords','')
        if search_keywords:
            all_courses = all_courses.filter(Q(name__icontains= search_keywords)|Q(desc__icontains=search_keywords)|Q(detail__icontains=search_keywords))#name__icontains contains前面的i表示不区分大小写

        #课程排序
        sort = request.GET.get('sort','')
        if sort:
            if sort == 'hot':
                all_courses = all_courses.order_by('-click_nums')
            elif sort == 'students':
                all_courses = all_courses.order_by('-student')

        try:
            page = int(request.GET.get('page', 1))#这里要做一下int转换,这里的request.GET.get('page', 1)中的page是Django在分页时自动生成的
        except PageNotAnInteger:
            page = 1
        paginator = Paginator(all_courses,6,request=request)#每页显示条数3
        courses = paginator.page(page)

        if request.user.is_authenticated:
            username = request.user
        else:
            username = '未登录，请点击登陆'

        return render(request,'course-list.html',{
            'all_courses': courses,
            'sort':sort,
            'hot_courses':hot_courses,
            'username':username,
        })


class CourseDetail(View):
    def get(self,request,course_id):
        course = Course.objects.get(id = int(course_id))
        course.click_nums+=1
        fav_count = UserFavorate.objects.filter(fav_type = 1,fav_id=course_id ).count()#当前课程的被收藏次数
        course.fav_nums = fav_count
        '''
        #当前课程的学习人数
        '''
        count = 0
        student_nums = UserCourse.objects.all()
        for student in student_nums:
           if student.course.id == course_id:
               count +=1
        course.student = count
        course.save()#记录点击课程的次数

        course_has_fav = False
        org_has_fav = False
        if request.user.is_authenticated:
            username = request.user
            user = UserProfile.objects.get(Q(username=username) | Q(email=username))
            user_id = user.id
            if UserFavorate.objects.filter(user_id=user_id, fav_id=course.id, fav_type=1):#从数据库中查询
                course_has_fav = True
            if UserFavorate.objects.filter(user_id = user_id ,fav_id = course.course_org.id,fav_type = 2):
                org_has_fav = True
        else:
            username = '未登录，请点击登陆'

        tag = course.tag
        if tag:
            relate_course = Course.objects.filter(tag = tag)
            relate_course = relate_course.exclude(id = course.id)[:1]#將當前課程排除在推薦課程之外
        else:
            relate_course = []
        return render(request,'course-detail.html',{
            'course':course,
            'username': username,
            'relate_course':relate_course,
            'course_has_fav':course_has_fav,
            'org_has_fav':org_has_fav
        })

class CourseInfoVideo(LoginRequiredMixin,View):#继承登陆验证函数，如果未登录则调转到登陆页面
    def get(self,request,course_id):
        course = Course.objects.get(id = int(course_id))
        course.student +=1
        course.save()
        resources = CourseResource.objects.filter(course = course)
        # pdb.set_trace()

        if request.user.is_authenticated:#该同学还学过哪些课程
            username = request.user
            user = UserProfile.objects.get(Q(username=username) | Q(email=username))
            user_id = user.id
            usercourse = UserCourse.objects.filter(user_id = user_id)[:5]
            user_course = UserCourse.objects.filter(user = username,course = course)
            if not user_course:#如果当前用户的课程学习没有保存这个门课程，这将这门课程保存到，这样用户的信息下
                user_course = UserCourse(user = username,course = course)
                user_course.save()

        return render(request,'course-video.html',{
            'course':course,
            'resources':resources,
            'usercourse':usercourse,
            'username':username
        })


class CourseCommentView(LoginRequiredMixin,View):
    def get(self,request,course_id):
        course = Course.objects.get(id = int(course_id))
        resources = CourseResource.objects.filter(course = course)
        all_comments = CourseComment.objects.filter(course = course)
        # pdb.set_trace()
        if request.user.is_authenticated:
            username = request.user
            user = UserProfile.objects.get(Q(username=username) | Q(email=username))
            user_id = user.id
            usercourse = UserCourse.objects.filter(user_id = user_id)[:5]

        return render(request,'course-comment.html',{
            'course':course,
            'resources':resources,
            'all_comments':all_comments,
            'usercourse': usercourse
        })

class AddCommentView(View):
    def post(self,request):
        '''
        用户添加课程评论
        :param request:
        :return:
        '''
        if not request.user.is_authenticated:
            return HttpResponse('{"status":"fail","msg":"用户未登陆"}',content_type='application/json')
        #post 到底是从哪里拿数据的,好像是前端的ajax
        course_id = request.POST.get('course_id',0)
        comment = request.POST.get('comments','')
        # pdb.set_trace()
        if int(course_id)>0 and comment:
            course_comment = CourseComment()
            course = Course.objects.get(id = int(course_id))
            course_comment.course = course
            course_comment.comment = comment
            course_comment.user = request.user
            course_comment.save()

            return HttpResponse('{"status":"success","msg":"添加评论成功"}',content_type='application/json')
        else:
            return HttpResponse('{"status":"fail","msg":"添加评论失败"}', content_type='application/json')


class VideoPlayView(View):
    def get(self,request,video_id):
        video = Video.objects.get(id = int(video_id))
        course = video.lesson.course
        resources = CourseResource.objects.filter(course = course)
        # pdb.set_trace()

        if request.user.is_authenticated:#该同学还学过哪些课程
            username = request.user
            user = UserProfile.objects.get(Q(username=username) | Q(email=username))
            user_id = user.id
            usercourse = UserCourse.objects.filter(user_id = user_id)[:5]
            user_course = UserCourse.objects.filter(user = username,course = course)
            if not user_course:#如果当前用户的课程学习没有保存这个门课程，这将这门课程保存到，这样用户的信息下
                user_course = UserCourse(user = username,course = course)
                user_course.save()

        return render(request,'course_play.html',{
            'course':course,
            'resources':resources,
            'usercourse':usercourse,
            'username':username,
            'video':video
        })


