from datetime import datetime

from django.db import models
from DjangoUeditor.models import UEditorField

class GoodsCategory(models.Model):
    CATEGORY_TYPE = (
        (1,'一级类别'),
        (2,'二级类别'),
        (3,'三级类别')
    )#做choice用

    name = models.CharField(max_length=50,verbose_name='类别名',default='',help_text='类别名')
    code = models.CharField(max_length=50, verbose_name='类别编号',default='',help_text='类别编号')
    desc = models.TextField(verbose_name='类别描述',help_text='类别描述')
    category_type = models.IntegerField(choices=CATEGORY_TYPE, verbose_name='类目级别',help_text='类目级别')
    parent_category = models.ForeignKey('self', verbose_name='父类目录级',null=True,blank=True,related_name='sub_cat',on_delete=models.CASCADE)
    is_tab = models.BooleanField(default=False, verbose_name='是否导航',help_text='是否导航')
    add_time = models.DateTimeField(default=datetime.now, verbose_name='添加时间')

    class Meta:
        verbose_name = u"商品类别"
        verbose_name_plural = verbose_name

    def __str__(self):#admin 管理时返回的题目标题
        return self.name


class GoodsCategoryBrand(models.Model):
    category = models.ForeignKey(GoodsCategory, verbose_name='商品类目', help_text='商品类目', on_delete=models.CASCADE)
    name = models.CharField(max_length=50, verbose_name='品牌名',help_text='品牌名',default='')
    desc = models.TextField(verbose_name='品牌描述',help_text='品牌描述',default='',max_length=500)
    image = models.ImageField(max_length=100, verbose_name='图片上传',upload_to='brands/')
    add_time = models.DateTimeField(default=datetime.now, verbose_name='添加时间')


    class Meta:
        verbose_name = u"品牌"
        verbose_name_plural = verbose_name

    def __str__(self):#admin 管理时返回的题目标题
        return self.name


class Goods(models.Model):
    category = models.ForeignKey(GoodsCategory,verbose_name='商品类目', help_text='商品类目',on_delete=models.CASCADE)
    name = models.CharField(max_length=50, verbose_name='商品名', help_text='品牌名', default='')
    goods_sn = models.CharField(max_length=50, verbose_name='商品货号', help_text='商品货号', default='')
    click_num = models.IntegerField(verbose_name='点击数', help_text='点击数', default=0)
    sold_num = models.IntegerField(verbose_name='售卖数', help_text='售卖数', default=0)
    goods_num = models.IntegerField(verbose_name='库存数', help_text='库存数', default=0)
    market_price = models.FloatField(verbose_name='市场价格', help_text='市场价格', default=0.0)
    shop_price = models.FloatField(verbose_name='售卖价格', help_text='售卖价格', default=0.0)
    goods_brief = models.CharField(max_length=500, verbose_name='商品简述', help_text='商品简述', default='')
    goods_desc = UEditorField(verbose_name='商品描述内容',imagePath='goods/images', filePath='goods/files',default='')
    # goods_desc = UEditorField(verbose_name='商品描述内容')
    ship_free = models.BooleanField(verbose_name='是否免运费', help_text='是否免运费', default=False)
    goods_front_image = models.ImageField(verbose_name='商品首页图', help_text='商品首页图',null= True,blank=True,upload_to='goods/images/')
    is_new = models.BooleanField(default=False, verbose_name='是否为新品')
    is_hot = models.BooleanField(verbose_name='是否为热销商品', default=False)

    add_time = models.DateTimeField(default=datetime.now, verbose_name='添加时间')

    class Meta:
        verbose_name = "商品"
        verbose_name_plural = verbose_name

    def __str__(self):#admin 管理时返回的题目标题
        return self.name


class GoodsImage(models.Model):
    goods = models.ForeignKey(Goods,verbose_name='商品',related_name='images',on_delete=models.CASCADE)
    image = models.ImageField(verbose_name='商品图片',upload_to='brands/images/')
    image_url = models.CharField(max_length=100, verbose_name='图片url')
    add_time = models.DateTimeField(default=datetime.now, verbose_name='添加时间')


    class Meta:
        verbose_name = '商品图片'
        verbose_name_plural = verbose_name

    def __str__(self):#admin 管理时返回的题目标题
        return self.goods.name


class Banner(models.Model):
    '''
    轮播商品
    '''
    goods = models.ForeignKey(Goods,verbose_name='商品',on_delete=models.CASCADE)
    image = models.ImageField(upload_to='banner/',verbose_name='轮播图')
    index = models.IntegerField(default=0,verbose_name='轮播顺序')
    add_time = models.DateTimeField(default= datetime.now,verbose_name='添加时间')

    class Meta:
        verbose_name = '轮播图片'
        verbose_name_plural = verbose_name

    def __str__(self):
        return self.goods.name
