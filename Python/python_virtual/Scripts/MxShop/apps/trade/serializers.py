import time

# from VueDjangoFrameWorkShop.settings import private_key_path, ali_pub_key_path
from goods.models import Goods
from goods.serializer import GoodsSerializer
from rest_framework import serializers,exceptions
from .models import ShoppingCart, OrderInfo, OrderGoods

# from utils.alipay import AliPay


class ShopCartDetailSerializer(serializers.ModelSerializer):
    # 一条购物车关系记录对应的只有一个goods。商品详情serializer
    goods = GoodsSerializer(many=False, read_only=True)

    class Meta:
        model = ShoppingCart
        fields = ("goods", "nums")


class ShopCartSerializer(serializers.Serializer):
    # 使用Serializer本身最好, 因为它是灵活性最高的。
    user = serializers.HiddenField(
        default=serializers.CurrentUserDefault()
    )
    nums = serializers.IntegerField(required=True, label="数量", min_value=1,
                                    error_messages={
                                        "min_value": "商品数量不能小于一",
                                        "required": "请选择购买数量"
                                    })
    goods = serializers.PrimaryKeyRelatedField(required=True, queryset=Goods.objects.all())

    def create(self, validated_data):
        if self.context["request"].user.is_anonymous:#没有当前用户时抛出异常
            raise exceptions.NotAuthenticated()
        else:
            user = self.context["request"].user

        nums = validated_data["nums"]
        goods = validated_data["goods"]
        existed = ShoppingCart.objects.filter(user=user, goods=goods)

        if existed:
            existed = existed[0]
            existed.nums += nums
            existed.save()
        else:
            existed = ShoppingCart.objects.create(**validated_data)

        return existed

    def update(self, instance, validated_data):
        # 修改商品数量
        instance.nums = validated_data["nums"]
        instance.save()
        return instance


class OrderGoodsSerialzier(serializers.ModelSerializer):
    goods = GoodsSerializer(many=False)
    class Meta:
        model = OrderGoods
        fields = "__all__"


class OrderSerializer(serializers.ModelSerializer):
    user = serializers.HiddenField(
        default=serializers.CurrentUserDefault()
    )

    #ready_only为只读形式前端不显示，只返回
    pay_status = serializers.CharField(read_only=True)
    trade_no = serializers.CharField(read_only=True)
    order_sn = serializers.CharField(read_only=True)
    pay_time = serializers.DateTimeField(read_only=True)

    # alipay_url = serializers.SerializerMethodField(read_only=True)

    # def get_alipay_url(self, obj):
    #     alipay = AliPay(
    #         appid="2016091200490210",
    #         app_notify_url="http://115.159.122.64:8000/alipay/return/",
    #         app_private_key_path=private_key_path,
    #         alipay_public_key_path=ali_pub_key_path,  # 支付宝的公钥，验证支付宝回传消息使用，不是你自己的公钥,
    #         debug=True,  # 默认False,
    #         return_url="http://115.159.122.64:8000/alipay/return/"
    #     )
    #
    #     url = alipay.direct_pay(
    #         subject=obj.order_sn,
    #         out_trade_no=obj.order_sn,
    #         total_amount=obj.order_mount,
    #     )
    #     re_url = "https://openapi.alipaydev.com/gateway.do?{data}".format(data=url)
    #
    #     return re_url
    #
    def generate_order_sn(self):
        # if self.context["request"].user.is_anonymous:#没有当前用户时抛出异常
        #     raise exceptions.NotAuthenticated()
        # 当前时间+userid+随机数
        from random import Random
        random_ins = Random()
        order_sn = "{time_str}{userid}{ranstr}".format(time_str=time.strftime("%Y%m%d%H%M%S"),
                                                       userid=self.context["request"].user.id,
                                                       ranstr=random_ins.randint(10, 99))

        return order_sn

    def validate(self, attrs):
        attrs["order_sn"] = self.generate_order_sn()
        return attrs

    class Meta:
        model = OrderInfo
        fields = "__all__"


class OrderDetailSerializer(serializers.ModelSerializer):
    # 一个订单有多个订单商品项
    goods = OrderGoodsSerialzier(many=True)
#
#     alipay_url = serializers.SerializerMethodField(read_only=True)
#
#     def get_alipay_url(self, obj):
#         alipay = AliPay(
#             appid="2016091200490210",
#             app_notify_url="http://115.159.122.64:8000/alipay/return/",
#             app_private_key_path=private_key_path,
#             alipay_public_key_path=ali_pub_key_path,  # 支付宝的公钥，验证支付宝回传消息使用，不是你自己的公钥,
#             debug=True,  # 默认False,
#             return_url="http://115.159.122.64:8000/alipay/return/"
#         )
#
#         url = alipay.direct_pay(
#             subject=obj.order_sn,
#             out_trade_no=obj.order_sn,
#             total_amount=obj.order_mount,
#         )
#         re_url = "https://openapi.alipaydev.com/gateway.do?{data}".format(data=url)
#
#         return re_url
#
    class Meta:
        model = OrderInfo
        fields = "__all__"