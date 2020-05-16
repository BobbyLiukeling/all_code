<template>
    <div class="main">
        <div class="homeLeft">
            <Car />
            <List />
            <lazy-component>
                <hot v-for="(item,index) in hostEssay" :key="index" :essay="hostEssay[index]" />
            </lazy-component>
            <PageList />
            <mainBottom />
        </div>
        <Affix class="homeRight" :offset-top="50">
            <rightMain />
        </Affix>
    </div>
</template>

<script>
import Car from '@/components/home/Car'
import List from '@/components/home/List'
import hot from '@/components/home/hot'
import PageList from '@/components/home/PageList'
import mainBottom from '@/components/home/mainBottom'
import rightMain from '@/components/home/rightMain'
import { hotEssay } from '@/assets/api/api'

export default {
    components:{
        Car,
        List,
        hot,
        PageList,
        mainBottom,
        rightMain
    },
    data(){
        return{
            hostEssay: []
        }
    },
    methods:{
        getessay(){
            hotEssay()
            .then( res => {
                this.hostEssay = res.data.data.essay
            })
            .catch( err => {
                console.log(err)
            })
        }
    },
    created() {
        this.getessay()
    },
}
</script>

<style scoped>
.main{
    padding-top: 30px;
    max-width: 1050px;
    margin: 0 auto;
    display: flex;
    justify-content: space-between;
}
.homeLeft{
    width: 70%;
}
.homeRight{
    width: 28%;
}
</style>
