# from .serializer import GoodsSerialize
# from rest_framework.views import APIView
# from rest_framework.response import Response
# from .models import Goods
# class GoodsListView(APIView):
#     """
#     List all snippets, or create a new snippet.
#     """
#     def get(self, request, format=None):
#         goods = Goods.objects.all()[:10]
#         goods_serializer = GoodsSerialize(goods, many=True)#mang = True 结果会序列化为一个数组对象
#         return Response(goods_serializer.data)

    # def post(self, request, format=None):
    #     serializer = GoodsSerialize(data=request.data)
    #     if serializer.is_valid():
    #         serializer.save()
    #         return Response(serializer.data, status=status.HTTP_201_CREATED)
    #     return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

# from rest_framework import mixins
# from rest_framework import generics
# from rest_framework import viewsets
#
# from .models import Goods
# from .serializer import GoodsSerialize
#
#
# class GoodsListView(mixins.ListModelMixin, mixins.CreateModelMixin, generics.GenericAPIView):
#     '''
#     queryset和serializer_class的名字不可以改变，因为所继承的generics.GenericAPIView源码里面的参数就是这个名字
#     '''
#     queryset = Goods.objects.all()
#     serializer_class = GoodsSerialize
#
#     def get(self, request, *args, **kwargs):
#         return self.list(request, *args, **kwargs)



from rest_framework import mixins,viewsets,filters
from rest_framework.pagination import PageNumberPagination
from django_filters.rest_framework import DjangoFilterBackend


from .filters import GoodsFilter
from .models import Goods,GoodsCategory
from .serializer import GoodsSerializer,GoodsCategorySerialize


class GoodsPagination(PageNumberPagination):
    page_size = 12
    # 向后台要多少条
    page_size_query_param = 'page_size'
    # 定制多少页的参数
    page_query_param = "page"
    max_page_size = 100



class GoodsListViewSet(mixins.ListModelMixin, mixins.RetrieveModelMixin, viewsets.GenericViewSet):

    '''
    url:goods/
    Goods views
    商品详情列表
    '''
    queryset = Goods.objects.all()
    serializer_class = GoodsSerializer
    pagination_class = GoodsPagination

    # 设置三大常用过滤器之DjangoFilterBackend, SearchFilter
    filter_backends = (DjangoFilterBackend, filters.SearchFilter, filters.OrderingFilter)
    # 设置排序
    ordering_fields = ('sold_num', 'shop_price','add_time')
    # 设置filter的类为我们自定义的类
    filter_class = GoodsFilter
    #设置查找字段
    search_fields = ('name', 'goods_brief', 'goods_desc')


class GoodsCategoryViewSet(mixins.ListModelMixin,mixins.RetrieveModelMixin, viewsets.GenericViewSet):#mixins.RetrieveModelMixin功能了解一下
    '''
    url:goods/category/
    GoodsCategory views
    商品分类页表
    '''
    # goods = GoodsCategory.objects.all()
    # a=1
    queryset = GoodsCategory.objects.filter(category_type=1)
    serializer_class = GoodsCategorySerialize



