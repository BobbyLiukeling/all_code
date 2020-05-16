from django.urls import path,re_path,include
from rest_framework.routers import DefaultRouter

from .views import GoodsListViewSet,GoodsCategoryViewSet

# list = GoodsListViewSet.as_view(
#     {
#         'get':'list',
#     }
# )
#
# urlpatterns = [
#     path('list/',list,name = 'list')
# ]

router = DefaultRouter()
router.register(r'list',GoodsListViewSet,base_name='list')
# router.register(r'categorys',GoodsCategoryViewSet,base_name='categorys')

urlpatterns = [
    path('',include(router.urls))
]