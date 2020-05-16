"""MxShop URL Configuration

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
from django.contrib import admin
from django.urls import path,include,re_path
import xadmin
from django.views.static import serve
from rest_framework.documentation import include_docs_urls
from rest_framework.routers import DefaultRouter
from goods.views import GoodsListViewSet,GoodsCategoryViewSet
from rest_framework import urls
from rest_framework.authtoken import views
from rest_framework_jwt.views import obtain_jwt_token
from MxShop.settings import MEDIA_ROOT
from users.views import SmsCodeView,UserViewSet
from user_operation.views import UserFavViewset,LeavingMessageViewset,AddressViewset
from trade.views import ShoppingCartViewset,OrderViewset

router = DefaultRouter()
#商品导航栏
router.register(r'categorys',GoodsCategoryViewSet,base_name='categorys')

#商品列表
router.register(r'goods',GoodsListViewSet,base_name='goods_list')

#返回的验证码接口
router.register(r'code',SmsCodeView,base_name='code')

#注册，为毛不叫register？
router.register(r'users',UserViewSet,base_name='users')

#用户收藏
router.register(r'userfavs',UserFavViewset,base_name='userfavs')

#用户留言
router.register('leavingmsg',LeavingMessageViewset,base_name='leavingmsg')

#收货地址
router.register('address',AddressViewset,base_name='address')

#购物车
router.register('shopcart',ShoppingCartViewset,base_name='shopcart')

#用户订单
router.register('order',OrderViewset,base_name='order')


#用户详情
# router.register(r'userlist',UserdetailViewSet,base_name='userlist')

# router.register(r'login',LoginView,base_name='login')

urlpatterns = [
    path('xadmin/', xadmin.site.urls),

    #UEDitor
    path('ueditor/',include('DjangoUeditor.urls')),

    #配置图片路径
    re_path(r'^media/(?P<path>.*)$', serve, { 'document_root': MEDIA_ROOT,}),

    path('docs/',include_docs_urls(title='慕学生鲜')),

    path('api-auth/', include('rest_framework.urls')),#用于调试api

    #将router注册
    path('',include(router.urls)),

    #用于用户登录,drf中的原生方法
    # path('api-token-auth/', views.obtain_auth_token),
    #用于用户登录，jwt中的方法
    path('login/', obtain_jwt_token),

]



