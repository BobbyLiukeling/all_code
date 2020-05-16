"""MXonline URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/2.0/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
import xadmin#用户名：bobby 密码：liukeling
from django.urls import path,include,re_path
from django.views.generic import TemplateView
from django.views.static import serve

# from users.views import LoginView, RegisterView,ActiveView,ForgetPwdView,ResetView,ModifyPwdView
# from organization.views import OrgView

from .settings import MEDIA_ROOT,STATICFILES_DIRS

from users.views import IndexView

urlpatterns = [
    path('xadmin/', xadmin.site.urls),
    path('', IndexView.as_view(), name="index"),#首页

    #index
    path('index/',include('users.urls'), name = 'home' ),
    #org
    path('org/',include('organization.urls'), name = 'org'),
    #course
    path('course/',include('courses.urls'), name = 'course'),


    #配置media图片的URL，上传文件的访问路径
    re_path(r'^media/(?P<path>.*)$', serve, { 'document_root': MEDIA_ROOT,}),
    # re_path(r'^static/(?P<path>.*)$', serve, { 'document_root': STATICFILES_DIRS[0],}),#配置静态文件路径
    #re_path('media/(?P<path>.*)/',serve,{'document_root':MEDIA_ROOT}),
    #配置验证码
    path('captcha/', include('captcha.urls')),

    #富文本编辑器
    path('ueditor/', include('DjangoUeditor.urls')),
]

#全局404，500页面配置，不一定要在user下面的views里面配置，
# handler403 = 'users.views.page_403'
# handler404 = 'users.views.page_not_found'
# handler500 = 'users.views.page_error'
