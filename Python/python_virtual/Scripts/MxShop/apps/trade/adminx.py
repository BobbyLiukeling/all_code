import xadmin

from .models import ShoppingCart,OrderInfo,OrderGoods


class ShoppingCartAdmin(object):
    list_display = ['user','goods','nums','add_time']
    list_filter = ['user__name','goods__name','nums','add_time']
    search_filter = ['user','goods','nums']


class OrderInfoAdmin(object):
    list_display = ['user','order_sn','trade_sn','pay_status','post_script','order_mount','pay_time'
        ,'address','signer_name','signer_mobile','add_time']
    list_filter = ['user__name','order_sn','trade_sn','pay_status','post_script','order_mount','pay_time'
        ,'address','signer_name','signer_mobile','add_time']
    search_filter = ['user','order_sn','trade_sn','pay_status','post_script','order_mount'
        ,'address','signer_name','signer_mobile']


class OrderGoodsAdmin(object):
    list_display = ['order','goods','goods_num','add_time']
    list_filter = ['order__order_sn','goods','goods_num','add_time']
    search_filter = ['order','goods','goods_num']



xadmin.site.register(ShoppingCart,ShoppingCartAdmin)
xadmin.site.register(OrderInfo,OrderInfoAdmin)
xadmin.site.register(OrderGoods,OrderGoodsAdmin)