<template>
    <div class="content">
        <div class="top">
            <div class="headImg"><img :src="essay.titleImg" alt="此处有图就显示，无图就不显示"></div>
            <div class="topMain">
                <div class="topMainTop">
                    <h2>{{essay.title}}</h2>
                    <p class="essayContent">{{essay.content}}</p>
                </div>
                <div class="topMainDown">
                    <span>发布于{{essay.date}}</span>
                    <span>发布者：{{essay.zuozhe}}</span>
                </div>
            </div>
        </div>
        <div class="bottom">
            <span>标签：{{essay.biaoqian}}</span>
            <span><i class="iconfont icon-message"/>{{essay.pinglun}}评论</span>
            <span><i class="iconfont icon-heart"/>点赞</span>
            <span><i class="iconfont icon-star"/>收藏</span>
            <span><i class="iconfont icon-error" @click="asd"/>举报</span>
        </div>
    </div>
</template>

<script>
export default {
    props: {
        essay :{}
    },
    data(){
        return{
        }
    },
    methods: {
        asd(){
            console.log(this.essay)
        }
    }
}
</script>

<style scoped>
.content{
    width: 100%;
    padding: 20px;
    display: flex;
    flex-direction: column;
    background-color: aliceblue;
    margin-top: 20px;
    border-radius: 5px;
}
.content .top{
    display: flex;
}
.content .top .headImg{
    width: 180px;
    height: 150px;
    background-color: aquamarine;
    overflow: hidden;
    border-radius: 4px;
}
.content .top .topMain{
    width: 65%;
    margin-left: 30px;
    text-align: left;
    font-size: 1rem;
    height: 150px;
    position: relative;
}
.content .top .topMain .topMainDown{
    position: absolute;
    bottom: 0;
    font-size: .8em;
}
.content .bottom{
    margin-top: 8px;
    text-align: left;
    font-size: 1em;
}
.content .bottom span{
    margin-right: 20px;
}
.headImg img{
    width: 100%;
    height: 100%;
}
.essayContent{
    padding-top: 14px;
    display: -webkit-box;
  overflow: hidden;
  -webkit-line-clamp: 4;
  color: #888;
  -webkit-box-orient: vertical;
}
</style>
