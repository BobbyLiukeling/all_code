<template>
    <div id="login">
        </br>
        <Tabs id="tab">
            <TabPane label="登录" name="name1">
                <div id="inputlog">
                    <div>
                        <Input prefix="ios-contact" placeholder="手机号或邮箱" style="width: 72%;"size="large"  />
                    </div>
                    <div>
                        <Input placeholder="密码" type="password" prefix="ios-unlock-outline" style="width: 72%" size="large" >
                        </Input>
                    </div>
                </div>
                <Checkbox size="large" id="remember">记住我</Checkbox>
                <a href=“” id="forget">登录失败?</a>
                </br>
                <Button @click="login" type="primary" shape="circle" size="large" style="width:70%;margin-top:10%;font-size:1.4em;">登  录</Button>
            </TabPane>
            <TabPane label="注册" name="name2">
                <div id="inputlog">
                    <div>
                        <Input prefix="ios-contact" placeholder="你的昵称" style="width: 72%;"size="large"  />
                    </div>
                    <div>
                        <Input placeholder="手机号" prefix="ios-call" style="width: 72%" size="large" >
                        </Input>
                    </div>
                    <div>
                        <Input placeholder="手机验证码" prefix="ios-mail-open" style="width: 72%" size="large" >
                        </Input>
                        <Button type="primary" shape="circle" style="position: absolute;right: -86%;height: 40px;background:rgb(83,210,107);border-color:rgb(83,210,107);">发送验证码</Button>
                    </div>
                    <div>
                        <Input placeholder="密码" type="password" prefix="ios-unlock-outline" style="width: 72%;" size="large" >
                        </Input>
                    </div>
                    <Button  type="primary" shape="circle" size="large" style="width:70%;margin-top:10%;font-size:1.4em;background:rgb(83,210,107);border-color:rgb(83,210,107);">注 册</Button>
                </div>
            </TabPane>
         </Tabs>
    </div>
</template>

<style>
    * {
        margin:0px auto;
        padding: 0px;
        font-family: 微软雅黑;
    }
    #tab {
        margin-top: 10%;
    }
    #login {
        width: 20%;
        height: 27vw;
        background:white;
    }
    .ivu-tabs-nav .ivu-tabs-tab {
        font-size: 2em;
    }
    .ivu-tabs-nav {
        width: 100%;
    } 
    .ivu-tabs-ink-bar {
        width:50%!important;
        background-color: rgb(244, 79, 79)
    }
    .ivu-tabs-nav .ivu-tabs-tab {
        width: 50%;
        color: rgb(173, 173, 173)
    }
    .ivu-tabs-nav .ivu-tabs-tab {
        margin: 0px;
    }
    .ivu-tabs-nav .ivu-tabs-tab-active {
        color:rgb(244, 79, 79)
    }
    .ivu-tabs-nav .ivu-tabs-tab:hover {
        color:rgb(244, 79, 79)
    }
    #inputlog {
        margin-top: 15%;
    }
    .ivu-input-large {
        height: 40px;
        background-color: rgba(244, 244, 244, 1);
    }
    .ivu-checkbox-large .ivu-checkbox-checked .ivu-checkbox-inner:after {
        width: 10px;
        height: 13px;
    }
    .ivu-checkbox-large .ivu-checkbox-inner {
        height: 21px;
        width: 21px;
    }
    #remember {
        margin-top: 10%;
        font-size: 1.4em;
        color: rgb(158, 158, 158)
    }
    .ivu-checkbox {
        width: 30px;
    }
    #forget {
        font-size: 1.4em;
        margin-left: 30%;
        color: rgb(163, 163, 163)
    }
</style>

<script>
    import store from '@/vuex/store'
    export default {
        methods:{
            login(){
                this.axios({
                    url:'http://127.0.0.1:8000/login/',
                    method: 'get',
                }).then(result => {
                    console.log(result);
                })
          }
        }
    }


</script>
