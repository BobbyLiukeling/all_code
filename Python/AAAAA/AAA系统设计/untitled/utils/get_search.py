from django.utils.safestring import mark_safe
class Page():

    def __init__(self, page_num, total_count, per_page=5, max_page=11):
        """

        :param page_num: 当前页码数
        :param total_count: 数据总数
        :param url_prefix: a标签href的前缀
        :param per_page: 每页显示多少条数据
        :param max_page: 页面上最多显示几个页码
        """
        self.max_page = max_page
        # 每一页显示多少条数据
        # 总共需要多少页码来展示
        total_page, m = divmod(total_count, per_page)
        if m:
            total_page += 1
        self.total_page = total_page

        try:
            page_num = int(page_num)
            # 如果输入的页码数超过了最大的页码数，默认返回最后一页
            if page_num > total_page:
                page_num = total_page
        except Exception as e:
            # 当输入的页码不是正经数字的时候 默认返回第一页的数据
            page_num = 1
        self.page_num = page_num

        # 定义两个变量保存数据从哪儿取到哪儿
        self.data_start = (page_num - 1) * 10
        self.data_end = page_num * 10

        # 页面上总共展示多少页码
        if total_page < self.max_page:
            self.max_page = total_page

        half_max_page = self.max_page // 2
        # 页面上展示的页码从哪儿开始
        page_start = page_num - half_max_page
        # 页面上展示的页码到哪儿结束
        page_end = page_num + half_max_page
        # 如果当前页减一半 比1还小
        if page_start <= 1:
            page_start = 1
            page_end = self.max_page
        # 如果 当前页 加 一半 比总页码数还大
        if page_end >= total_page:
            page_end = total_page
            page_start = total_page - self.max_page + 1
        self.page_start = page_start
        self.page_end = page_end

    @property
    def start(self):
        return self.data_start

    @property
    def end(self):
        return self.data_end


    def page_html(self):
        # 自己拼接分页的HTML代码
        html_str_list = []
        # 加上第一页
        html_str_list.append('<li><a href="{}?page=1">首页</a></li>'.format( self.url_prefix))

        # 判断一下 如果是第一页，就没有上一页
        if self.page_num <= 1:
            html_str_list.append('<li class="disabled"><a href="#"><span aria-hidden="true">&laquo;</span></a></li>'.format(self.page_num-1))
        else:
            # 加一个上一页的标签
            html_str_list.append('<li><a href="{}?page={}"><span aria-hidden="true">&laquo;</span></a></li>'.format( self.url_prefix, self.page_num-1))

        for i in range(self.page_start, self.page_end+1):
            # 如果是当前页就加一个active样式类
            if i == self.page_num:
                tmp = '<li class="active"><a href="{0}?page={1}">{1}</a></li>'.format(self.url_prefix, i)
            else:
                tmp = '<li><a href="{0}?page={1}">{1}</a></li>'.format( self.url_prefix, i)

            html_str_list.append(tmp)

        # 加一个下一页的按钮
        # 判断，如果是最后一页，就没有下一页
        if self.page_num >= self.total_page:
            html_str_list.append('<li class="disabled"><a href="#"><span aria-hidden="true">&raquo;</span></a></li>')
        else:
            html_str_list.append('<li><a href="{}?page={}"><span aria-hidden="true">&raquo;</span></a></li>'.format( self.url_prefix, self.page_num+1))
        # 加最后一页
        html_str_list.append('<li><a href="{}?page={}">尾页</a></li>'.format(self.url_prefix, self.total_page))

        page_html = "".join(html_str_list)
        return mark_safe(page_html)