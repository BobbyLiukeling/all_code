import json



from django.views.generic.base import View
from django.http import HttpResponse,JsonResponse
from django.forms.models import model_to_dict
from django.core import serializers


from goods.models import Goods


class GoodsListView(View):
    '''
    商品列表页
    '''
    def get(self,request):
        goods = Goods.objects.all()[:10]
        # json_list = []
        # for good in goods:
        #     json_dict = {}
        #     json_dict['name'] = good.name
        #     json_dict['category'] = good.category.name
        #     json_dict['market_price'] = good.market_price
        #     json_list.append(json_dict)
        # for good in goods:
        #     json_dict = model_to_dict(good)
        #     json_list.append(json_dict)
        # return HttpResponse(json.dumps(json_list),content_type='application/json')
        json_data = serializers.serialize('json',goods)#将数据库中取出的内容转换为json
        json_data = json.loads(json_data)#将json数据转换为字符数据
        return JsonResponse(json_data,safe=False)




