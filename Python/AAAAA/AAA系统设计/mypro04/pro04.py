from exception import userLoginException,userPassException,userPassSameException,userNoExitException,userPassErrorException
class   userManager:
    def __init__(self):
        self.userFile = 'users.txt'

    def userPhoneCheck(self, phone):
        if len(phone) == 11:
            return True
        else:
            try:
                raise userLoginException()
            except userLoginException as a:
                print(a)
                return False

    def userPassCheck(self, password):
        if len(password) == 6:
            return True
        else:
            try:
                raise userPassException()
            except userPassException as a:
                print(a)
                return False
    def userRegister(self,phone,password,rePassword):
        if password != rePassword:
            try:
                raise userPassSameException()
            except userPassSameException as a:
                print(a)
                return False
        elif rePassword==password:
            with open(self.userFile,'a',encoding='utf-8') as f:
                temp = phone+" "+password+'\n'
                f.write(temp)
                return True
        else:
            print("注册出错，请重新检查")
            return False


    def userLogin(self,phone,password):
        try:
            file=open(self.userFile,'r',encoding='utf-8')
            for line in file:
                line = line.strip()
                line_user_list = line.split(" ")
                if line_user_list[0]==phone and line_user_list[1]==password:
                    return True
                elif line_user_list[0]==phone and line_user_list[1]!=password:
                    try:
                        raise userPassErrorException()
                    except userPassErrorException as a:
                        print(a)
                        return False
        except IOError:
            print("文件不存在")
            return False

    def phone_exist(self,phone):
        try:
            with open(self.userFile,'r',encoding='utf-8') as f:
                for line in f:
                    line = line.strip()
                    line_Phone=line.split(" ")
                    if line_Phone[0]== phone:
                        return True
                return False
        except IOError:
            return False

    def main(self):
        print('******欢迎来到用户管理系统******')
        while(True):
            arg = input("1:注册,2:登录,3:退出登录\n")
            if arg=='1':
                print('******欢迎来到注册界面******')
                phone = input('请输入你的手机号码\n')
                if self.phone_exist(phone):
                    print("该手机用户已存在")
                    continue
                elif not self.userPhoneCheck(phone):
                    # print("请输入11位的手机号")
                    continue
                else:
                    pwd = input("请设置密码\n")
                    if not self.userPassCheck(pwd):
                        continue
                    else:
                        pwd1 = input("请再次确认密码\n")
                    if self.userRegister(phone,pwd,pwd1):
                        print("你的{}手机号注册成功".format(phone))
                        continue
                    else:
                        print("注册失败")
                        continue
            if arg=='2':
                print("******欢迎来到登入界面******")
                phone = input("请输入你的手机号\n")
                if not self.phone_exist(phone):
                    try:
                        raise userNoExitException()
                    except userNoExitException as a:
                        print(a)
                        continue
                else:
                    pwd2 = input("请输入对应的密码\n")
                    if self.userLogin(phone,pwd2):
                        print("登录成功")
                        continue
                    else:
                        print("登录失败，请重新填写信息")
                        continue
            elif arg=='3':
                phone = input("请输入需要退出的用户手机号\n")
                if not self.phone_exist(phone):
                    print("没有该用户存在")
                    continue
                else:
                    print("{}退出登录".format(phone))
                    continue
            else:
                print("输入错误格式，请重新输入")
                continue

