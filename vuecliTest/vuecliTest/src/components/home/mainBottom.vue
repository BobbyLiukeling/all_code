<template>
    <div class="tan">
        <ul>
            <li v-for="(item, index) in content" >{{item}}</li>
        </ul>
    </div>
</template>

<script>
export default {
    data(){
        return{
            content: [
                '关于知程',
                '联系我们',
                '加入我们',
                '评判与标徽',
                '帮助中心',
                '合作伙伴'
            ]
        }
    }
}
</script>

<style scoped>
.tan{
    height: 200px;
    background-color: blueviolet;
    margin-bottom: 100px;
}
.tan ul{
    display: flex;
    justify-content: space-around;
    align-items: center;
    font-size: 17px;
    color: aquamarine;
}
</style>
