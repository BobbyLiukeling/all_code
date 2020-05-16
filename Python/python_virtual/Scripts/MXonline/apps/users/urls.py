from django.urls import path,re_path

from .views import LoginView, RegisterView,ActiveView,ForgetPwdView,ResetView,ModifyPwdView,LogoutView
from .views import UserInfoView,UploadImgView,ResetPwdView,ResetEmailView,EmailVerifyView,ResetUserInfoView,UserCourseView,test
from .views import UserFavCourseView,UserFavOrgView,UserFavTeacherView,UserMsgView
urlpatterns = [
    #name 的作用是在前端配置路由的时候使用 url 'message:getpost'这个getpost是name = 'getpost'中的getpost
    path('login/',LoginView.as_view(), name="login"),
    path('logout/',LogoutView.as_view(), name="logout"),#退出登录
    path('register/',RegisterView.as_view(), name="register"),
    re_path(r'active/(?P<active_code>[0-9]{6})/$', ActiveView.as_view(),name = "user_active"),
    path('forget/',ForgetPwdView.as_view(),name = "forget_pwd"),
    re_path(r'reset/(?P<active_code>[0-9]{6})/$',ResetView.as_view(),name = "reset_pwd"),
    path('modify_pwd/',ModifyPwdView.as_view(),name = "modify_pwd"),
    path('userinfo/',UserInfoView.as_view(),name = "user_info"),
    path('user_img_upload/',UploadImgView.as_view(),name = "img_upload"),
    path('reset_pwd/',ResetPwdView.as_view(),name = "reset_pwd"),
    path('reset_email/',ResetEmailView.as_view(),name = "reset_email"),
    path('send_emailcode/',EmailVerifyView.as_view(),name = "send_emailcode"),
    path('info/',ResetUserInfoView.as_view(),name = "info"),
    path('usercourse/',UserCourseView.as_view(),name = "user_course"),
    path('user_favcourse/',UserFavCourseView.as_view(),name = "user_favcourse"),
    path('user_favorg/',UserFavOrgView.as_view(),name = "user_favorg"),
    path('user_favteacher/',UserFavTeacherView.as_view(),name = "user_favteacher"),
    path('usermessage/',UserMsgView.as_view(),name = "user_msg"),
    path('test/',test.as_view(),name = "test"),
]









