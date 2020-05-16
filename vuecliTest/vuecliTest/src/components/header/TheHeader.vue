<template>
    <div class="header">
        <div ref="allmap"></div>
        <div class="main">
            <div class="mainLeft">
                <div class="logo">logo</div>
                <span><i class="iconfont icon-home"/>首页</span>
                <span><i class="iconfont icon-compass"/>关注</span>
                <span><i class="iconfont icon-bulb"/>提问</span>
                <Badge :count="userInfo.msg" :offset=[12,0] v-if="userInfo.id"><i class="iconfont icon-bell"/>消息</Badge>
                <div class="search">
                    <div class="searchm">
                        <Cascader :data="provinceList" :render-format="format" :placeholder="userInfo.city||city||'地域'"></Cascader>
                        <input placeholder="热门文档"/>
                        <Icon size=38 type="ios-search-outline" />
                    </div>
                </div>
            </div>
            <div class="mainRight">
                <div class="login" v-if="!userInfo.name">
                    <span class="a">登录</span>
                    <span class="log">注册</span>
                </div>
                <div class="user" v-else>
                    <span class="headImg"><img :src="userInfo.imgUrl" alt=""></span>
                </div>
                <div class="editor">
                    <span @click="show">写文件</span>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
import {provinceList} from '../../assets/area.js'
import { mapState } from 'vuex'
import cookie from '../../assets/cookie.js'
import { autoLogon } from '../../assets/api/api'

export default {
    data(){
        return{
            showclass: true,
            provinceList,
            city: '',
        }
    },
    computed: {
        ...mapState(['userInfo'])
    },
    watch: {
        city(){}
    },
    methods: {
        show(){
            this.showclass = !this.showclass
        },
        map(){
          var that = this
          var geolocation = new BMap.Geolocation();
          geolocation.getCurrentPosition(function(r){
            if(this.getStatus() == BMAP_STATUS_SUCCESS){
                that.city = r.address.city
            }
            else {
                alert('failed'+this.getStatus());
            }        
            })
        },
        format(lab,sel){
            const index = lab.length - 1;
            const data = sel[index] || false;
            if (data && data.code) {
                return lab[index] + ' - ' + data.code;
            }
            return lab[index];
        }
    },
    mounted() {
        //初始化
        //先检测是否之前有登录
        this.$store.dispatch('initUser')
        if( !this.userInfo.id ){
            //如果没有登录，获取地址，把地址传入vuex中保存
            this.map()
        }
    },
}
</script>

<style scoped>
i{
    font-size: 30px;
}
.header{
    background-color: #f7fdfb;
    border-bottom: solid 1px #e3e5e4;
}
.header .main{
    max-width: 1050px;
    height: 50px;
    margin: 0 auto;
    display: flex;
    justify-content: space-between;
    align-items: stretch;
}
.header .main .mainLeft{
    width: 70%;
    display: flex;
    justify-content: space-between;
    align-items: stretch;
}
.header .main .mainLeft span{
    padding: 5px;
    display: flex;
    align-items: center;
}
.header .main .mainLeft span:hover{
    transition: .3s;
    background-color: #defbe9;
}
.header .main .mainLeft .logo{
    display: flex;
    align-items: center;
    width: 50px;
    background-color: #91fe8b;
    border-radius: 3px;
}
.header .main .mainLeft .search{
    width: 40%;
    background-color: #f7fdfb;
    display: flex;
    justify-content: center;
    align-items: center;
}
.header .main .mainLeft .search .searchm{
    width: 100%;
    height: 40px;
    margin-left: 20px;
    border-radius: 20px;
    background-color: #eeeeee;
    display: flex;
    justify-content: flex-start;
}
.header .main .mainLeft .search .searchm .ivu-icon{
    border-radius: 20px;
    border: solid 1px #aeeaac;
}
.header .main .mainLeft .search .searchm .ivu-icon::before{
    position: relative;
    color: #5dff67;
    vertical-align: middle;
}
.header .main .mainRight{
    width: 30%;
    display: flex;
    justify-content: center;
    align-items: center;
}
.header .main .mainRight .login,
.header .main .mainRight .user,
.header .main .mainRight .editor{
    width: 60%;
    height: 40px;
    display: flex;
    justify-content: center;
    align-items: center;
}
.header .main .mainRight .login .a{
    width: 40%;
    font-size: 20px;
}
.header .main .mainRight .login .log{
    width: 40%;
    font-size: 20px;
    border-radius: 5px;
    border: solid 1px #fbaaa9;
    color: #ff615f;
}
.header .main .mainRight .editor{
    width: 40%;
    background-color: #ff5d5e;
    font-size: 20px;
    color: #f7fdfb;
    border-radius: 20px;
}
input{
    margin-left: 4px;
    border: none;
    background-color: transparent;
}
input:focus{
    outline: none;
    background-color: transparent;
}
.headImg{
    height: 40px;
    width: 40px;
    border-radius: 25px;
    overflow: hidden;
}
.headImg img{
    width: 100%;
    height: 100%;
}

</style>
<style>
.header .main .mainLeft .search .searchm .ivu-cascader-rel .ivu-input-wrapper-default input{
    height: 40px;
    width: 80px;
    border-radius: 20px;
    background-color: #ffffff;
}
.header .main .mainLeft .search .searchm .ivu-input-wrapper-default input{
    height: 100%;
    background-color: transparent;
    border: none;
    transition-property: none;
}
.header .main .mainLeft .search .searchm .ivu-input-wrapper-default input:focus{
    /* height: 100%;
    background-color: transparent;
    border: none;
    outline-color: #91fe8b;
    transition-property: none;
    outline: none; */
}
</style>

