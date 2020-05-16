<template>
    <div class="box" ref="box">
        <span v-for="item in list">{{item}}</span>
        <span @click="showMore">更多<Icon type="md-arrow-dropdown" /></span>
        <span v-for="item in list">{{item}}</span>
    </div>
</template>

<script>
export default {
    data(){
        return{
            tan : true,
            list : [
                1,2,3,4,5,6,7,8,9
            ]
        }
    },
    methods : {
        showMore(){
            console.log(this.tan)
            if(this.tan)
            this.$refs.box.style.animation =  'show .3s ease forwards'
            else
            this.$refs.box.style.animation =  'hide .3s ease forwards'
            this.tan = !this.tan
            console.log(this.tan)
        }
    }
}
</script>

<style scoped>
.box{
    margin-top: 30px;
    display: flex;
    height: 110px;
    flex-wrap: wrap;
    align-content: flex-start;
    background-color: aquamarine;
    overflow: hidden;
    border-radius: 5px;
    
}
span{
    font-size: 15px;
    width: 120px;
    border-radius: 4px;
    margin: 8px;
    margin-left: 17px;
    height: 40px;
    background-color: rgb(128, 219, 219);
    line-height: 40px;
}
</style>
<style>
@keyframes show {
    0% {
        height: 110px;
    }
    100%{
        height: 220px;
    }
}
@keyframes hide {
    0% {
        height: 220px;
    }
    100%{
        height: 110px;
    }
}
</style>


