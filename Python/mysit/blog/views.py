from django.shortcuts import render
from . import models
# Create your views here.

def home(request):
    articles = models.Ariticle.objects.all()
    return render(request,"blog/templates/message_form.html",{'key':articles})


def article_page(request,article_id):
    article = models.Ariticle.objects.get(pk=article_id)
    return render(request, 'blog/templates/article_page.html', {'article':article})

def edit_page(request,article_id):
    if str(article_id) == '0':
        return render(request,"blog/templates/edit_page.html")
    article = models.Ariticle.objects.get(pk = article_id)
    return render(request, "blog/templates/edit_page.html",{'article' : article})

def edit_action(request):
    title = request.POST.get("title","TITLE")
    content = request.POST.get("content", "CONTENT")
    article_id = request.POST.get('article_id','0')

    if article_id == '0':
        models.Ariticle.objects.create(title=title, content=content)
        articles = models.Ariticle.objects.all()
        return render(request,"blog/templates/message_form.html",{'key':articles})

    article = models.Ariticle.objects.get(pk = article_id)
    article.title = title
    article.content = content
    article.save()
    return render(request, "blog/templates/article_page.html", {'article': article})
