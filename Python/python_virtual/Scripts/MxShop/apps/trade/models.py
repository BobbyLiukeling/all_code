from datetime import datetime

from django.db import models
from django.contrib.auth import get_user_model#拿到userprofile
User = get_user_model()

from goods.models import Goods


class ShoppingCart(models.Model):
    user = models.ForeignKey(User,verbose_name='用户',on_delete=models.CASCADE)
    goods = models.ForeignKey(Goods,verbose_name='商品',on_delete=models.CASCADE)
    nums = models.IntegerField(default=0,verbose_name='购买数量')
    add_time = models.DateTimeField(default=datetime.now, verbose_name='添加时间')

    class Meta:
        verbose_name = "购物车"
        verbose_name_plural = verbose_name
        unique_together = ('user','goods')

    def __str__(self):#admin 管理时返回的题目标题
        return "%s(%d)".format(self.goods.name,self.goods_nums)


class OrderInfo(models.Model):
    '''
    订单
    '''
    ORDER_STATUS = (
        ('success','成功'),
        ('cancal','取消'),
        ('cancal','待支付')
    )
    # PAY_TYPE = (
    #     ('alipay','支付宝'),
    #     ('wechat','微信')
    # )
    user = models.ForeignKey(User,verbose_name='用户',on_delete=models.CASCADE)
    order_sn = models.CharField(max_length=30,verbose_name='订单编号')#订单编号
    trade_sn = models.CharField(max_length=100,unique=True,null=True,blank=True,verbose_name='交易编号')#交易编号
    pay_status = models.CharField(choices=ORDER_STATUS,max_length=10,verbose_name='订单状态')
    post_script = models.CharField(max_length=10,verbose_name='订单留言')
    order_mount = models.FloatField(default=0.0,verbose_name='点单金额')
    pay_time = models.DateTimeField(null=True,blank=True,verbose_name='支付时间')
    address = models.CharField(max_length=100,default='',verbose_name='收货地址')
    signer_name = models.CharField(max_length=20,default='',verbose_name='签收人')
    signer_mobile = models.CharField(max_length=11,verbose_name='联系电话')
    add_time = models.DateTimeField(default=datetime.now, verbose_name='添加时间')

    class Meta:
        verbose_name = "订单"
        verbose_name_plural = verbose_name

    def __str__(self):#admin 管理时返回的题目标题
        return str(self.order_sn)


class OrderGoods(models.Model):
    '''
    订单的商品详情
    '''
    order = models.ForeignKey(OrderInfo,verbose_name='订单信息',on_delete=models.CASCADE,related_name='goods')
    goods = models.ForeignKey(Goods,verbose_name='商品',on_delete=models.CASCADE)
    goods_num = models.IntegerField(default=0,verbose_name='商品数量')
    add_time = models.DateTimeField(default=datetime.now, verbose_name='添加时间')

    class Meta:
        verbose_name = "订单商品"
        verbose_name_plural = verbose_name

    def __str__(self):#admin 管理时返回的题目标题
        return str(self.order.order_sn)
