import xadmin

from .models import GoodsCategory,GoodsCategoryBrand,Goods,GoodsImage,Banner


class GoodsCategoryAdmin(object):
    list_display = ['name','code','desc','category_type','parent_category','is_tab','add_time']
    list_filter = ['name','code','desc','category_type','parent_category','is_tab','add_time']
    search_fields = ['name','code','desc','category_type','parent_category','is_tab']


class GoodsCategoryBrandAdmin(object):
    list_display = ['category','name','desc','image','add_time']
    list_filter = ['category__name','name','desc','image','add_time']
    search_fields = ['category','name','desc','image']


class GoodsAdmin(object):
    list_display =  ['category','name','goods_sn','click_num','sold_num','goods_num','market_price',
                    'shop_price','goods_brief','goods_desc','ship_free','goods_front_image','is_new','is_hot','add_time']
    list_filter = ['category__name','name','goods_sn','click_num','sold_num','goods_num','market_price',
                    'shop_price','goods_brief','goods_desc','ship_free','goods_front_image','is_new','is_hot','add_time']
    search_fields = ['category','name','goods_sn','click_num','sold_num','goods_num','market_price',
                    'shop_price','goods_brief','goods_desc','ship_free','goods_front_image','is_new','is_hot']

    style_fields = {"goods_desc": "ueditor"}


class GoodsImageAdmin(object):
    list_display = ['goods','image','image_url','add_time']
    list_filter = ['goods__name','image','image_url','add_time']
    search_fields = ['goods','image','image_url']


class BannerAdmin(object):
    list_display = ['goods','image','index','add_time']
    list_filter = ['goods__name','image','index','add_time']
    search_fields =['goods','image','index']


xadmin.site.register(GoodsCategory,GoodsCategoryAdmin)
xadmin.site.register(GoodsCategoryBrand,GoodsCategoryBrandAdmin)
xadmin.site.register(Goods,GoodsAdmin)
xadmin.site.register(GoodsImage,GoodsImageAdmin)
xadmin.site.register(Banner,BannerAdmin)