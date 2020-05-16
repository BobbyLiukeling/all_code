from django.shortcuts import render,render_to_response
from .models import UserMessage
import pdb
# Create your views here.
def getform(request):
    all_message = UserMessage.objects.all()#从数据库中查询数据
    for message in all_message:
        print(message)
    m = UserMessage.objects.get(pk=1)    # 从数据库中查询数据
    #m.delete()#从数据流中删除这条语句


    # render(request, template_name, context=None, content_type=None, status=None, using=None):
    #template_name,是放置HTML文件的位置路径
    return render(request, "message/templates/message_form.html",{'m':m})
    #return render(request, "message/templates/message_form.html")

def getpost(request):
    if request.method == 'POST':
        name = request.POST.get('name', '')  # 获取前端数据
        message = request.POST.get('message', '')
        address = request.POST.get('address', '')
        email = request.POST.get('email', '')
        # 将数据写到数据库
        message2 = UserMessage()  # 定义数据库
        message2.name = name
        message2.message = message
        message2.address = address
        message2.email = email
        message2.save()  # 保存
    name = request.POST.get('name',"no")
    context = {'b':name}
    return render(request,"message/templates/post.html",context)

    # c = csrf(request)
    # c.update({'b':name})
    # return render_to_response('message/templates/post.html',context=c)



