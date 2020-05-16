from django.shortcuts import render, HttpResponse, redirect, HttpResponseRedirect
from app01.models import *
import random
import os
from utils.pagenation import Pagination
import xlwt
from io import BytesIO
from django.db.models import Q
from django.db.models import F
import copy
'''倒的包，用的模块'''


# Create your views here.
def login(request):
    msg = {}
    if request.method == 'POST':
        '''定义一个字典，发送post请求,找用户名'''
        username = request.POST['username']
        manager = Manager.objects.filter(manage_name=username).first()
        teacher = App01Teacher.objects.filter(teacher_no=username).first()
        '''先从老师里面找，再从管理员里面找'''
        if manager:  # 老师登陆
            password = request.POST.get('password')
            '''如果老师存在，就获取密码，如果密码匹配，就登录成功'''
            db_password = manager.password
            if password == db_password:
                request.session['name'] = manager.name
                request.session['id'] = manager.id
                return redirect('/teacher/')
            else:
                msg = {'msg': '密码错误'}
                '''密码错误就返回到登录页面'''
                return render(request, 'login.html', locals())

        elif teacher != '':  # 管理员登陆
            '''如果管理员不为空，就获取他的密码，进行密码匹配，如果密码匹配，就登录成功'''
            password = request.POST.get('password')
            db_password = teacher.password
            if password == db_password:
                request.session['teacher_name'] = teacher.teacher_name
                request.session['teacher_no'] = teacher.teacher_no
                return redirect('/teacher/')
            else:
                msg = {'msg': '密码错误'}
                '''密码错误就返回到登录页面'''
                return render(request, 'login.html', locals())
        else:
            msg = {'msg': '用户名不存在'}
            '''用户名不存在也返回到登录页面'''
            return render(request, 'login.html', locals())
    return render(request, 'login.html')


def logout(request):

    name = request.session["name"]
    if name:
        del request.session["name"]
        '''老师退出登录。
        django中使用session来保存用户登录状态
        如果session里面有name这个名字，就把他删掉'''
        return HttpResponseRedirect("/login/")
    else:
        del request.session["teacher_name"]
        '''如果session里面有teacher_name这个名字，就把他删掉'''
        return HttpResponseRedirect("/login/")


def logout_teachername(request):
    teacher = request.session["teacher_name"]
    if teacher:
        del request.session["teacher_name"]
        return HttpResponseRedirect("/login/")
    else:
        return HttpResponseRedirect("/login/")


'''统计页面'''


def teacher(request):
    all_student = int(App01Student.objects.all().count())
    '''拿到所有学生，将每一类的学生统计出来，每一类的除以所有学生，在乘100%'''
    han_um = int(App01Student.objects.filter(nation="汉族").count())
    han = "%.2f%%" % ((han_um / all_student) * 100)
    ''' %.2f表示输出浮点数并保留两位小数。%%表示直接输出一个%。'''
    hui_num = int(App01Student.objects.filter(nation='回族').count())
    hui = "%.2f%%" % ((hui_num / all_student) * 100)
    Uyghur_num = int(App01Student.objects.filter(nation='维吾尔族').count())
    Uyghur = "%.2f%%" % ((Uyghur_num / all_student) * 100)
    Kazak_num = int(App01Student.objects.filter(nation='哈萨克族').count())
    Kazak = "%.2f%%" % ((Kazak_num / all_student) * 100)
    Mongol_num = int(App01Student.objects.filter(nation='蒙古族').count())
    Mongol = "%.2f%%" % ((Mongol_num / all_student) * 100)
    return render(request, 'html/index.html', locals())


'''老师页面'''


def manager(request):
    classes = App01Student.objects.values("classes").distinct()
    nation = App01Student.objects.values("nation").distinct()
    query = request.GET.get("query", "")
    '''首先从前端获取查询的条件，并且此条件可以为空'''
    q = Q()
    q.connector = "OR"
    '''利用django的Q搜索方法来进行“或”查询，其中所有条件都可以查询'''
    q.children.append(Q(("student_name__contains", query)))
    q.children.append(Q(("student_no__contains", query)))
    q.children.append(Q(("male__contains", query)))
    q.children.append(Q(("nation__contains", query)))
    q.children.append(Q(("classes__contains", query)))
    q.children.append(Q(("apartment__dormitoryno__contains", query)))
    q.children.append(Q(("apartment__apartment_no__apartment_name__contains", query)))
    query_params = copy.deepcopy(request.GET)
    '''如果从数据库后台传过来的值包括学生的姓名、学号、性别、民族、班级、宿舍等信息，
       在前台就可以利用学生的所有信息精准查询出来'''

    ret = App01Student.objects.filter(q).values("student_no", "student_name", "male", "nation",
                                                "classes", "contact", "apartment__apartment_no__apartment_name",
                                                "apartment__dormitoryno",
                                                )
    '''利用django的filter方法来筛选某一条件，再将除了筛选的那个条件的所有条件信息全部查询出来。'''
    '''分页'''
    page = Pagination(request, ret.count(), query_params, per_num=10)
    return render(request, 'html/foot.html', {"ret": ret[page.start:page.end],
                                              "html_str": page.show_li,
                                              "classes": classes,
                                              "nation": nation
                                              })


def add_student(request):
    if request.method == "POST":
        '''向后台发送post请求，点添加之后，这些所有的信息都可以添加。'''
        student_no = request.POST.get('student_no')
        student_name = request.POST.get('student_name')
        classes = request.POST.get('classes')
        male = request.POST.get('male')
        contact = request.POST.get('contact')
        apartment = request.POST.get('apartment')
        nation = request.POST.get('nation')
        App01Student.objects.create(student_no=student_no, student_name=student_name,
                                    classes=classes, male=male, apartment_id=apartment,
                                    contact=contact, nation=nation)
        return redirect('/student_list/')
    new_student_list = App01Student.objects.all()
    '''利用filter筛选后，只显示汉族学生小于4的，少数民族信息小于2的宿舍信息'''
    empty_apartment = App01Apartment.objects.filter(han__lte=4, others__lte=2)
    return render(request, 'html/add_student.html', {"student_list": new_student_list,
                                                     "empty": empty_apartment})

'''信息查询'''


def student_list(request):
    classes = App01Student.objects.values("classes").distinct()
    nation = App01Student.objects.values("nation").distinct()
    query = request.GET.get("query", "")
    '''首先从前端获取查询的条件，并且此条件可以为空'''
    q = Q()
    q.connector = "OR"
    '''利用django的Q方法来进行“或”查询，其中所有条件都可以查询'''
    q.children.append(Q(("student_name__contains", query)))
    q.children.append(Q(("student_no__contains", query)))
    q.children.append(Q(("male__contains", query)))
    q.children.append(Q(("nation__contains", query)))
    q.children.append(Q(("classes__contains", query)))
    q.children.append(Q(("apartment__dormitoryno__contains", query)))
    q.children.append(Q(("apartment__apartment_no__apartment_name__contains", query)))

    query_params = copy.deepcopy(request.GET)
    '''如果从数据库后台传过来的值包括学生的姓名、学号、性别、民族、班级、宿舍等信息，
    在前台就可以利用学生的所有信息精准查询出来'''

    ret = App01Student.objects.filter(q).values("student_no", "student_name", "male", "nation",
                                                "classes", "contact", "apartment__apartment_no__apartment_name",
                                                "apartment__dormitoryno",
                                                )
    '''利用django的filter方法来筛选某一条件，再将除了筛选的那个条件的所有条件信息全部查询出来。'''
    '''分页'''
    page = Pagination(request, ret.count(), query_params, per_num=10)
    return render(request, 'html/student_list.html', {"ret": ret[page.start:page.end],
                                                      "html_str": page.show_li,
                                                      "classes": classes,
                                                      "nation": nation
                                                      })


def delete_student(request):
    delete_id = request.GET.get('id')
    App01Student.objects.get(student_no=delete_id).delete()
    return redirect("/student_list/")

'''修改学生信息'''


def edit_student(request):
    if request.method == "POST":
        edit_name = request.POST.get('name')
        edit_no = request.POST.get('no')
        edit_male = request.POST.get('male')
        edit_classes = request.POST.get('classes')
        apartment = request.POST.get("apartment")
        edit_contact = request.POST.get('contact')
        App01Student.objects.filter(student_no=edit_no).update(student_name=edit_name, male=edit_male
                                                               , classes=edit_classes,
                                                               contact=edit_contact, apartment=apartment)

        return redirect("/student_list/")
    '''从前台获取id，判断是男生还是女生，如果是男生，只显示男生宿舍，如果是女生，只显示女生宿舍。
    然后就在数据库里面取值了，获取姓名、学号、性别、班级、宿舍、联系方式等。
    利用filter来筛选出学号，根据学号来更新姓名、性别、班级、宿舍等信息'''
    edit_id = request.GET.get("id")
    male_index = request.GET.get("male")
    if male_index == "男" and edit_id:
        edit_student.obj = App01Student.objects.get(student_no=edit_id)
        empty_apartment = App01Apartment.objects.filter(apartment_no=1,han__lt=4,others__lt=2).all()
        return render(request, 'html/edit_student.html', {'edit_student': edit_student.obj,
                                                          "empty": empty_apartment})
    elif male_index == "女" and edit_id:
        edit_student.obj = App01Student.objects.get(student_no=edit_id)
        empty_apartment = App01Apartment.objects.filter(apartment_no=2,han__lt=4,others__lt=2).all()

        return render(request, 'html/edit_student.html', {'edit_student': edit_student.obj,
                                                          "empty": empty_apartment})


'''未分配宿舍的学生'''


def unallocated(request):

    query = request.GET.get("query", "")
    '''首先从前端获取查询的条件，并且此条件可以为空'''
    q = Q()
    q.connector = "OR"
    '''利用django的Q方法来进行“或”查询，其中所有条件都可以查询'''
    q.children.append(Q(("student_name__contains", query)))
    q.children.append(Q(("student_no__contains", query)))
    q.children.append(Q(("male__contains", query)))
    q.children.append(Q(("nation__contains", query)))
    q.children.append(Q(("classes__contains", query)))
    query_params = copy.deepcopy(request.GET)
    '''如果从数据库后台传过来的值包括学生的姓名、学号、性别、民族、班级等信息，在前台就可以利用学生的所有信息精准查询出来'''

    row = App01Student.objects.filter((q), apartment=None).all()
    '''利用django的filter方法来筛选某一条件，再将除了筛选的那个条件的所有条件信息全部查询出来。'''
    '''分页'''
    page = Pagination(request, row.count(), query_params, per_num=10)
    return render(request, 'html/Unallocated.html', {"row": row[page.start:page.end],
                                                     "html_str": page.show_li, })


'''多条件查询'''


def text_allocation(request):
    classes = App01Student.objects.values("classes").distinct()
    nation = App01Student.objects.values("nation").distinct()
    male = request.GET.get("male", "")
    all_classes = request.GET.get('classes', "")
    all_nation = request.GET.get("nation", "")

    condition = {
        "male": male,
        "classes": all_classes,
        "nation": all_nation,
    }
    all_student = App01Student.objects.filter(**condition).values("student_no", "student_name", "male", "nation",
                                                                  "classes", "contact",
                                                                  "apartment__apartment_no__apartment_name",
                                                                  "apartment__dormitoryno", )
    query_params = copy.deepcopy(request.GET)
    '''分页'''
    page = Pagination(request, all_student.count(), query_params, per_num=10)
    return render(request, 'html/allocation.html', {"ret": all_student[page.start:page.end],
                                                    "html_str": page.show_li,
                                                    "classes": classes,
                                                    "nation": nation
                                                    })


'''分配宿舍'''

def foo(request):
    msg = {}
    classes = App01Student.objects.values("classes").distinct()
    nation = App01Student.objects.values("nation").distinct()
    male = request.GET.get("male")
    all_classes = request.GET.get('classes')
    all_nation = request.GET.get("nation")
    condition = {
        "male": male,
        "classes": all_classes,
        "nation": all_nation,
    }
    all_student = list(App01Student.objects.filter(**condition))
    student_li_li = []
    while len(all_student) > 0:
        if male == "男":
            result = random.randint(0, len(all_student) - 1)
            y = all_student[result].student_no
            apartment_index = all_student[result].apartment
            apartment = random.sample(list(App01Apartment.objects.filter(apartment_no_id=1).values('id')), 1)
            x = apartment[0]['id']
            han = list(App01Apartment.objects.filter(id=x).values("han"))
            han_info = han[0]['han']
            ment = list(App01Apartment.objects.filter(id=x).values("id"))
            ment_info = ment[0]['id']
            other = list(App01Apartment.objects.filter(id=x).values("others"))
            other_info = other[0]['others']

            del all_student[result]
            if all_nation == "汉族" and int(han_info) < 4 and apartment_index is None:
                App01Student.objects.filter(student_no=y).update(apartment=ment_info)
                obj = App01Apartment.objects.filter(id=x)
                obj.update(han=F('han') + 1)
                student = list(
                    App01Student.objects.filter(student_no=y).values("student_no", "student_name", "male",
                                                                     "nation",
                                                                     "classes", "contact",
                                                                     "apartment__apartment_no__apartment_name",
                                                                     "apartment__dormitoryno", ))

                student_li_li.append(student[0])

            elif int(other_info) < 2 and apartment_index is None:
                App01Student.objects.filter(student_no=y).update(apartment=ment_info)
                obj = App01Apartment.objects.filter(id=x)
                obj.update(others=F('others') + 1)
                student = list(
                    App01Student.objects.filter(student_no=y).values("student_no", "student_name", "male",
                                                                     "nation",
                                                                     "classes", "contact",
                                                                     "apartment__apartment_no__apartment_name",
                                                                     "apartment__dormitoryno", ))

                student_li_li.append(student[0])
        else:
            result = random.randint(0, len(all_student) - 1)
            y = all_student[result].student_no
            apartment_index = all_student[result].apartment
            apartment = random.sample(list(App01Apartment.objects.filter(apartment_no_id=2).values('id')), 1)
            x = apartment[0]['id']
            han = list(App01Apartment.objects.filter(id=x).values("han"))
            han_info = han[0]['han']
            ment = list(App01Apartment.objects.filter(id=x).values("id"))
            ment_info = ment[0]['id']
            other = list(App01Apartment.objects.filter(id=x).values("others"))
            other_info = other[0]['others']
            del all_student[result]
            if all_nation == "汉族" and int(han_info) < 4 and apartment_index is None:
                App01Student.objects.filter(student_no=y).update(apartment=ment_info)
                obj = App01Apartment.objects.filter(id=x)
                obj.update(han=F('han') + 1)
                student = list(
                    App01Student.objects.filter(student_no=y).values("student_no", "student_name", "male",
                                                                     "nation",
                                                                     "classes", "contact",
                                                                     "apartment__apartment_no__apartment_name",
                                                                     "apartment__dormitoryno", ))

                student_li_li.append(student[0])

            elif int(other_info) < 2 and apartment_index is None:
                App01Student.objects.filter(student_no=y).update(apartment=ment_info)
                obj = App01Apartment.objects.filter(id=x)
                obj.update(others=F('others') + 1)
                student = list(App01Student.objects.filter(student_no=y).values("student_no", "student_name", "male",
                                                                                "nation",
                                                                                "classes", "contact",
                                                                                "apartment__apartment_no__apartment_name",
                                                                                "apartment__dormitoryno", ))
                student_li_li.append(student[0])
    '''分页功能'''
    query_params = copy.deepcopy(request.GET)
    page = Pagination(request, len(student_li_li), query_params, per_num=30)
    return render(request, "html/ceshi.html", {"classes": classes,
                                               "nation": nation,
                                               'all_student': student_li_li[page.start:page.end],
                                               "html_str": page.show_li,
                                               "len": len(student_li_li)
                                               })


'''查看宿舍'''


def show_apartment(request):
    classes = App01Student.objects.values("classes").distinct()
    nation = App01Student.objects.values("nation").distinct()
    '''首先从前端获取查询的条件，并且此条件可以为空'''
    query = request.GET.get("query", "")
    '''利用django的Q方法来进行“或”查询，其中所有条件都可以查询'''
    q = Q()
    q.connector = "OR"
    '''如果从数据库后台传过来的值包括学生的宿舍号、宿舍楼等任一信息，在前台就可以利用学生的所有信息精准查询出来'''
    q.children.append(Q(("dormitoryno__contains", query)))
    q.children.append(Q(("apartment_no__apartment_name__contains", query)))
    query_params = copy.deepcopy(request.GET)
    '''利用django的filter方法来筛选某一条件，再将除了筛选的那个条件的所有条件信息全部查询出来。'''
    ret = App01Apartment.objects.filter(q).values("apartment_no__apartment_name",
                                                  "dormitoryno", "han", 'others')
    '''分页功能'''
    page = Pagination(request, ret.count(), query_params, per_num=10)
    return render(request, 'html/apartment.html', {"ret": ret[page.start:page.end],
                                                   "html_str": page.show_li,
                                                   "classes": classes,
                                                   "nation": nation
                                                   })


'''导出excel'''

'''调用django的xlwt方法导出excel
创建一个workbook,设置编码
创建一个 宿舍名单
写入excel，参数对应的是行、列、名称'''


def excel_export(request):
    ws = xlwt.Workbook(encoding='utf-8')
    w = ws.add_sheet(u"宿舍名单", cell_overwrite_ok=True)
    w.write(0, 0, 'test')
    activitys = list(App01Student.objects.values("student_no", "student_name", "male",
                                                 "nation",
                                                 "classes", "contact",
                                                 "apartment__apartment_no__apartment_name",
                                                 "apartment__dormitoryno"))
    student_index = []
    if activitys:
        w.write(0, 0, u"学号")
        w.write(0, 1, u"姓名")
        w.write(0, 2, u"性别")
        w.write(0, 3, u"民族")
        w.write(0, 4, u"班级")
        w.write(0, 5, u"宿舍楼号")
        w.write(0, 6, u"宿舍号")
        excel_row = 1
        for activity in activitys:
            student_index.append(activity)
            '''遍历'''
            for i in student_index:
                student_no = i['student_no']
                student_name = i['student_name']
                male = i['male']
                nation = i['nation']
                classes = i['classes']
                apartment_num = i['apartment__apartment_no__apartment_name']
                apartment_do = i['apartment__dormitoryno']
                w.write(excel_row, 0, student_no)
                w.write(excel_row, 1, student_name)
                w.write(excel_row, 2, male)
                w.write(excel_row, 3, nation)
                w.write(excel_row, 4, classes)
                w.write(excel_row, 5, apartment_num)
                w.write(excel_row, 6, apartment_do)
            excel_row += 1
        exist_file = os.path.exists('test.xls')
        if exist_file:
            os.remove(r'test.xls')
        ws.save('test.xls')
        sio = BytesIO()
        ws.save(sio)
        sio.seek(0)
        response = HttpResponse(sio.getvalue(), content_type='application/vnd.ms-excel')
        response['Content-Disposition'] = 'attachment; filename=test.xls'
        response.write(sio.getvalue())
        return response


'''教师管理'''


def show_manager(request):
    manager = Manager.objects.all()
    '''显示所有的教师页面，locals是将manager变量传到前台去'''
    return render(request, 'html/manager.html', locals())


def add_manager(request):
    if request.method == 'POST':
        '''发送post请求，在实例化'''
        manager = Manager()
        manager.name = request.POST.get('name')
        manager.manage_name = request.POST.get('manager_name')
        manager.password = request.POST.get('password')
        '''从前端用post方法获取参数'''
        manager.save()
        return redirect('/show_manager/')
    return render(request, 'html/add_manager.html')


def edit_manager(request):
    if request.method == "POST":
        '''发送post请求，得到请求后，密码不为空，就修改密码，如果密码为空，就修改其他的信息'''
        if request.POST.get('password') != '':
            Manager.objects.filter(id=request.POST.get('id')).update(manage_name=request.POST.get('manage_name'),
                                                                     password=request.POST.get('password'),
                                                                     name=request.POST.get('name')
                                                                     )
        else:
            Manager.objects.filter(id=request.POST.get('id')).update(manage_name=request.POST.get('manage_name'),
                                                                     name=request.POST.get('name')
                                                                     )

            return redirect("/show_manager/")
    edit_id = request.GET.get("id")
    manager = Manager.objects.filter(id=edit_id).all()
    return render(request, 'html/edit_manager.html', {'manager': manager})


def del_manager(request):
    delete_id = request.GET.get('id')
    Manager.objects.get(id=delete_id).delete()
    return redirect("/show_manager/")


'''修改老师密码'''


def changePasswordteacher(request):
    teacher_name = request.session["name"]
    name = Manager.objects.filter(name=teacher_name).values('name')
    if request.method == 'POST':
        if teacher_name:
            '''发送post请求，如果密码存在，不为空，就直接修改。'''
            if request.POST.get('password') != '':
                Manager.objects.filter(name=teacher_name).update(password=request.POST.get('password'))
                return HttpResponseRedirect('/teacher/')
    return render(request, 'html/changePassword.html', locals())


'''修改管理员'''


def changePasswordmanager(request):
    teacher = request.session["teacher_name"]
    managerInfo = App01Teacher.objects.filter(teacher_name=teacher).values()
    if request.method == 'POST':
        if teacher:
            '''发送post请求，如果密码存在，不为空，就直接修改。'''
            if request.POST.get('password') != '':
                App01Teacher.objects.filter(teacher_name=teacher).update(password=request.POST.get('password'))
                return HttpResponseRedirect('/teacher/')
    return render(request, 'html/changemanager.html', locals())
