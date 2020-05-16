<template>
    <Page :total="100" show-elevator @on-change="pageNum" />
</template>

<script>
export default {
    methods: {
        pageNum(item){
            console.log(item)
        }
    }
}
</script>

<style>
.ivu-page{
    margin: 30px 0;
}
</style>
