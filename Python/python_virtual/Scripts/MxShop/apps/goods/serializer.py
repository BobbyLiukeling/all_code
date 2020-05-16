from rest_framework import serializers
from .models import Goods,GoodsCategory,GoodsImage




class GoodsCategorySerialize3(serializers.ModelSerializer):
    class Meta:
        model = GoodsCategory
        fields = "__all__"#和forms.py 的功能一样，但是serializer可以不指明字段，直接写all，即使用全部字段


class GoodsCategorySerialize2(serializers.ModelSerializer):
    '''
    arent_category = models.ForeignKey('self', verbose_name='父类目录级'related_name='sub_cat')
    sub_cat 是在modes.py中GoodsCategory中定义字段时就定义好了的
    '''
    sub_cat = GoodsCategorySerialize3(many=True)#
    class Meta:
        model = GoodsCategory
        fields = "__all__"#和forms.py 的功能一样，但是serializer可以不指明字段，直接写all，即使用全部字段


class GoodsCategorySerialize(serializers.ModelSerializer):
    sub_cat = GoodsCategorySerialize2(many=True)
    class Meta:
        model = GoodsCategory
        fields = "__all__"#和forms.py 的功能一样，但是serializer可以不指明字段，直接写all，即使用全部字段


class GoodsImageSerializer(serializers.ModelSerializer):
    class Meta:
        model = GoodsImage
        fields = ("image",)


class GoodsSerializer(serializers.ModelSerializer):#serializers.ModelSerializer不再继承serializers.Serializer了
    category = GoodsCategorySerialize()#category 为goods的外键这里直接继承外键的内容，就可以将外键的内容全部显示,但是前端无影响！！！
    images = GoodsImageSerializer(many=True)
    class Meta:
        model = Goods
        fields = "__all__"


# class GoodsSerialize(serializers.Serializer):
#     name = serializers.CharField(max_length=50,default='')
#     click_num = serializers.IntegerField(default=0)