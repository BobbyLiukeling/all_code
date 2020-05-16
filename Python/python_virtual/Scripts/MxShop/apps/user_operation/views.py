from django.shortcuts import render
from rest_framework import viewsets
from rest_framework import mixins,exceptions
import pdb
from .models import UserFav, UserLeavingMessage, UserAddress
# from .serializers import UserFavSerializer, UserFavDetailSerializer, LeavingMessageSerializer, AddressSerializer
from .serializers import UserFavSerializer,UserFavDetailSerializer,LeavingMessageSerializer,AddressSerializer
from rest_framework.permissions import IsAuthenticated
from utils.permissions import IsOwnerOrReadOnly
from rest_framework_jwt.authentication import JSONWebTokenAuthentication
from rest_framework.authentication import SessionAuthentication


class UserFavViewset(viewsets.GenericViewSet,mixins.CreateModelMixin,mixins.ListModelMixin,
                     mixins.DestroyModelMixin,mixins.RetrieveModelMixin):
    """
    list:
        获取用户收藏列表
    retrieve:
        判断某个商品是否已经收藏
    create:
        收藏商品
    """
    # queryset = UserFav.objects.all()
    #验证是否登陆
    permission_classes = (IsAuthenticated, IsOwnerOrReadOnly)
    # permission_classes = (IsAuthenticated,)
    serializer_class = UserFavSerializer
    # 用户权限认证
    authentication_classes = (JSONWebTokenAuthentication, SessionAuthentication)#不知道是干啥的

    #只获取当前用户收藏
    def get_queryset(self):
        return UserFav.objects.filter(user=self.request.user)

    '''
    http://127.0.0.1:8000/userfavs/19/
    lookup_field = 'goods_id' 则上面链接中的19，就是goods_id 在数据库中的值，
    如果不设置lookup_field字段，那么上面的19就是默认的当前serializer_class所对应的的数据表的主键ID
    '''
    lookup_field = 'goods_id'
    # lookup_field = 'goods'


    # 收藏数+1
    # def perform_create(self, serializer):
    #     instance = serializer.save()
    #     # 通过这个instance Userfav找到goods
    #     goods = instance.goods
    #     goods.fav_num +=1
    #     goods.save()



    #设置动态的Serializer
    def get_serializer_class(self):
        # pdb.set_trace()
        if self.action == "list":
            return UserFavDetailSerializer
        elif self.action == "create":
            return UserFavSerializer

        return UserFavSerializer


class LeavingMessageViewset(mixins.ListModelMixin, mixins.DestroyModelMixin, mixins.CreateModelMixin,
                            viewsets.GenericViewSet):
    """
    list:
        获取用户留言
    create:
        添加留言
    delete:
        删除留言功能
    """

    permission_classes = (IsAuthenticated, IsOwnerOrReadOnly)
    authentication_classes = (JSONWebTokenAuthentication, SessionAuthentication)
    serializer_class = LeavingMessageSerializer

    # 只能看到自己的留言
    def get_queryset(self):
        if self.request.user.is_anonymous:
            raise exceptions.NotAuthenticated()
        else:
            return UserLeavingMessage.objects.filter(user=self.request.user)
#
#
class AddressViewset(viewsets.ModelViewSet):#ModelViewSet继承了所有mixin中的类
    """
    收货地址管理
    list:
        获取收货地址
    create:
        添加收货地址
    update:
        更新收货地址
    delete:
        删除收货地址
    """
    permission_classes = (IsAuthenticated, IsOwnerOrReadOnly)
    authentication_classes = (JSONWebTokenAuthentication, SessionAuthentication)
    serializer_class = AddressSerializer

    def get_queryset(self):
        if self.request.user.is_anonymous:
            raise exceptions.NotAuthenticated()
        else:
            return UserLeavingMessage.objects.filter(user=self.request.user)