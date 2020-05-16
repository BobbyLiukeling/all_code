class MyException(Exception):

    def __init__(self, *args):
        self.args = args

class userLoginException(MyException):

    def __init__(self,args =('请输入11位的手机号',)):
        self.args = args

class userPassException(MyException):
    def __init__(self, args =('请输入六位数字的密码',)):
        self.args = args

class userPassSameException(MyException):
    def __init__(self,args = ('密码不一致',)):
        self.args = args

class userNoExitException(MyException):
    def __init__(self,args = ('该手机号用户不存在，请先完成注册',)):
        self.args = args

class userPassErrorException(MyException):
    def __init__(self,args = ('密码错误',)):
        self.args = args