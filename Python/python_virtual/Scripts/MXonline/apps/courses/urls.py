from django.urls import path,re_path
from .views import CourseList,CourseDetail,CourseInfoVideo,CourseCommentView,AddCommentView,VideoPlayView


urlpatterns = [
    #name 的作用是在前端配置路由的时候使用 url 'message:getpost'这个getpost是name = 'getpost'中的getpost
    path('list/',CourseList.as_view(), name="course_list"),
    re_path('detail/(?P<course_id>\d*)/$',CourseDetail.as_view(), name="course_detail"),#\d*表示匹配0到多个数字
    re_path('info/(?P<course_id>\d*)/$',CourseInfoVideo.as_view(), name="course_info"),
    re_path('comment/(?P<course_id>\d*)/$',CourseCommentView.as_view(), name="course_comment"),
    path('add_comment/',AddCommentView.as_view(),name ="course_add_comment"),
    re_path('video/(?P<video_id>\d*)/$',VideoPlayView.as_view(), name="video_play"),
]









