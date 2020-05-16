<template>
    <Carousel autoplay loop>
        <CarouselItem v-for="(item, index) in list" :key=index>
            <div class="demo-carousel">
                <img :src="item.imgUrl" alt="">
                <!-- {{item.imgUrl}} -->
            </div>
        </CarouselItem>
    </Carousel>
</template>
<script>
import { hotEssay, lunbo } from '../../assets/api/api'
    export default {
        data () {
            return {
                list : []
            }
        },
        methods: {
            getLunbo(){
                lunbo()
                .then(res => {
                    this.list = res.data.list
                })
            }       
        },
        mounted() { 
            this.getLunbo()
        },
    }
</script>
<style scoped>
.demo-carousel{
    width: 100%;
    height: 300px;
    background-color: aquamarine;
}

</style>
<style>
.ivu-carousel{
    border-radius: 10px;
    overflow: hidden;
}
</style>


