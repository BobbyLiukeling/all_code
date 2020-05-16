<template>
    <div class="rightMain">
        <div class="list"><span>热门推荐</span></div>
        <div class="list"><span>优秀文档</span></div>
        <div class="list"><span>知程版权</span></div>
        <div class="list"><span>更多资讯</span></div>
        <div class="rightDown" v-if="$store.state.userInfo.id">
            <Card>
                <p slot="title" style="text-align: left">历史记录</p>
                <a href="#" slot="extra">更多<i class="iconfont icon-right" /></a>
                <ul>
                    <li v-for="(item,index) in historyList" :key="index">
                        <span>{{item.date}}</span>
                        <div class="littleImg"><img v-if="item.titleImg" :src="item.titleImg" alt=""></div>
                        <span class="title">{{item.title}}</span>
                        <a href="#"><i class="iconfont icon-delete" /></a>
                    </li>
                </ul>
            </Card>
        </div>
    </div>
</template>

<script>
import { history } from '../../assets/api/api'



export default {
    data(){
        return{
            historyList: []
        }
    },
    methods: {
        setHistory(){
            history(this.$store.state.userInfo.id).then( res => {
                this.historyList = res.data.list
            })
        }
    },
    mounted() {
        this.setHistory()
    },
}
</script>

<style scoped>
.rightMain .list{
    height: 60px;
    margin-bottom: 19px;
    font-size: 1.5em;
    line-height: 60px;
}
.rightMain .list:nth-child(1){
    background-color: #fe9778;
    color: #fffeff;
}
.rightMain .list:nth-child(2){
    background-color: #f2debd;
    color: #f6a41a;
}
.rightMain .list:nth-child(3){
    background-color: #b9f1cc;
    color: #15c50e;
}
.rightMain .list:nth-child(4){
    background-color: #b8f0ed;
    color: #158eff;
}
li .littleImg{
    width: 50px;
    height: 50px;
    background-color: #b9f1cc;
}
li .littleImg img{
    width: 100%;
    height: 100%;
}
li{
    height: 80px;
    display: flex;
    justify-content: space-between;
    align-items: center;
    font-size: 12px;
}
li .title{
    width: 40%;
    white-space: nowrap;
    overflow: hidden;
    text-overflow: ellipsis;
}
</style>
