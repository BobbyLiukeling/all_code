<template>
    <div class="user">
        <div class="left">
            <div class="top">
                <div class="headimg">
                    <img :src="$store.state.userInfo.imgUrl" alt="">
                </div>
                <div class="main">
                    <h3>{{$store.state.userInfo.name}}</h3>
                    <p><span>个性签名：</span><span><Button type="success" ghost>编辑个人资料</Button></span></p>
                </div>
            </div>
            <div class="nav">
                <Tabs value="name1">
                    <TabPane label="动态" name="name1"></TabPane>
                    <TabPane label="提问" name="name2"></TabPane>
                    <TabPane label="回答" name="name3"></TabPane>
                    <TabPane label="上传" name="name4"></TabPane>
                    <TabPane label="收藏" name="name5"></TabPane>
                    <TabPane label="关注" name="name6"></TabPane>
                </Tabs>
            </div>
            <div class="content">
                <h1>neirong</h1>
            </div>
        </div>
        <div class="right"></div>
    </div>
</template>

<script>
export default {

}
</script>

<style scoped>
.user{
    padding-top: 30px;
    max-width: 1050px;
    margin: 0 auto;
    display: flex;
    justify-content: space-between;
}
.user .left{
    width: 70%;
}
.user .right{
    width: 28%;
}
.user .left .top{
    display: flex;
    justify-content: center;
    background-color: #ffffff;
    padding: 20px;
    border-radius: 4px;
    box-shadow: 4px 4px 9px rgb(165, 165, 165);
}
.user .left .top .headimg{
    width: 20%;
}
.user .left .top .main{
    width: 75%;
    height: 100%;
    text-align: left;
}
.user .left .top .headimg img{
    border-radius: 50px;
}
.user .left .top .main h3{
    font-size: 24px;
    padding: 10px 0px 20px 0px;
}
.user .left .top .main p{
    font-size: 14px;
    height: 40px;
    line-height: 40px;
    display: flex;
    justify-content: space-between;
}
.user .left .top .main p span{
    line-height: 40px;
}
.user .left .nav{
    background-color: #ffffff;
    margin-top: 20px;
    border-radius: 4px;
    box-shadow: 4px 4px 9px rgb(165, 165, 165);
}
.user .left .content{
    min-height: 400px;
    border-radius: 5px;
    background-color: #ffffff;
    margin-top: 20px;
    border-radius: 4px;
    box-shadow: 4px 4px 9px rgb(165, 165, 165);
}
</style>
<style>
.user .left .nav .ivu-tabs .ivu-tabs-bar{
    margin-bottom: 0!important;
}
.user .left .nav .ivu-tabs .ivu-tabs-bar .ivu-tabs-nav-container{
    font-size: 16px;
}
</style>

