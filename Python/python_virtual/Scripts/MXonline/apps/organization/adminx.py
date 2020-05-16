from .models import CityDict,CourseOrg,Teacher,ZeroTeacher
import xadmin



class CityDictAdmin(object):#城市
    list_display = ["name","desc","add_time"]
    list_filter =["name","desc","add_time"]
    search_fields = ["name","desc"]


class CourseOrgAdmin(object):#课程机构
    list_display = ["name", "desc", "click_nums","fav_nums","img","address","city","add_time"]
    list_filter =["name", "desc", "click_nums","fav_nums","img","address","city__name","add_time"]
    search_fields =["name", "desc", "click_nums","fav_nums","img","address","city__name"]
    relfield_style = 'fk-ajax'#当CourseOrg作为其他字段的外键的时候，在后台其他数据表不再使用下拉的方式选择此数据表，而是搜索的方式出现


class TeacherAdmin(object):#教师信息
    list_display = ["org", "name", "work_years","work_company","work_position","points","click_nums","fav_nums","add_time"]
    list_filter =["org__name", "name", "work_years","work_company","work_position","points","click_nums","fav_nums","add_time"]
    search_fields =["org", "name", "work_years","work_company","work_position","points","click_nums","fav_nums"]

    # def get_list_queryset(self):
    def queryset(self):
        qs = super(TeacherAdmin,self).queryset()
        qs.filter(click_nums = True)
        return qs


class ZeroTeacherAdmin(object):#教师信息
    list_display = ["org", "name", "work_years","work_company","work_position","points","click_nums","fav_nums","add_time"]
    list_filter =["org__name", "name", "work_years","work_company","work_position","points","click_nums","fav_nums","add_time"]
    search_fields =["org", "name", "work_years","work_company","work_position","points","click_nums","fav_nums"]

    def queryset(self):
        qs = super(ZeroTeacherAdmin,self).queryset()
        qs.filter(click_nums = 0)
        return qs


xadmin.site.register(CityDict,CityDictAdmin)
xadmin.site.register(CourseOrg,CourseOrgAdmin)
xadmin.site.register(Teacher,TeacherAdmin)
xadmin.site.register(ZeroTeacher,ZeroTeacherAdmin)
