from rest_framework.validators import UniqueTogetherValidator
from rest_framework import serializers
from .models import UserFav,UserLeavingMessage,UserAddress
from goods.serializer import GoodsSerializer



class UserFavDetailSerializer(serializers.ModelSerializer):
    # 通过goods_id拿到商品信息。就需要嵌套的Serializer
    goods = GoodsSerializer()

    class Meta:
        model = UserFav
        fields = ("goods", "id")

class UserFavSerializer(serializers.ModelSerializer):
    # user = serializers.HiddenField(#收藏使用当前用户
    #     default=serializers.CurrentUserDefault()
    # )

    class Meta:
        model = UserFav

        # 使用validate方式实现唯一联合
        # validators = [
        #     UniqueTogetherValidator(
        #         queryset=UserFav.objects.all(),
        #         fields=('user', 'goods'),
        #         message="已经收藏"#消息会返回到前端
        #     )
        # ]

        fields = ("user", "goods", "id")


class LeavingMessageSerializer(serializers.ModelSerializer):
    user = serializers.HiddenField(
        default=serializers.CurrentUserDefault()
    )
    add_time = serializers.DateTimeField(read_only=True, format='%Y-%m-%d %H:%M')

    class Meta:
        model = UserLeavingMessage
        fields = ("user", "message_type", "subject", "message", "file", "id", "add_time")
#
#
class AddressSerializer(serializers.ModelSerializer):
    user = serializers.HiddenField(
        default=serializers.CurrentUserDefault()
    )
    add_time = serializers.DateTimeField(read_only=True, format='%Y-%m-%d %H:%M')

    class Meta:
        model = UserAddress
        fields = ("id", "user", "district", "address", "signer_name", "add_time", "signer_mobile")
