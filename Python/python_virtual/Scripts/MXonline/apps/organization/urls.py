from django.urls import path,include,re_path

from .views import OrgView,AddUserAskViwe,OrgHomeView,OrgCourseView,OrgDescView,OrgTeacherView,AddFavViews,TeacherListView,TeacherDetailView

urlpatterns = [
    # 课程机构首页
    path('list/', OrgView.as_view(), name="org_list"),
    path('add_ask/',AddUserAskViwe.as_view(),name = "org_add_ask"),
    re_path(r'^home/(?P<org_id>\d*)/$',OrgHomeView.as_view(),name = 'org_home'),
    re_path(r'^course/(?P<org_id>\d*)/$',OrgCourseView.as_view(),name = 'org_course'),
    re_path(r'^desc/(?P<org_id>\d*)/$',OrgDescView.as_view(),name = 'org_desc'),
    re_path(r'^teacher/(?P<org_id>\d*)/$',OrgTeacherView.as_view(),name = 'org_teacher'),
    path('teacher/list/',TeacherListView.as_view(),name = 'teacher_list'),
    path('add_fav/',AddFavViews.as_view(),name = 'org_add_fav'),
    re_path('teacher/detail/(?P<teacher_id>\d*)/$',TeacherDetailView.as_view(),name = 'teacher_detail'),
]