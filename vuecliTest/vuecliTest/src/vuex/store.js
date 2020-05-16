import Vue from 'vue';
import Vuex from 'vuex';
Vue.use(Vuex);

const state={
    count:1
}

const mutations={
    regist(){
        this.axios({
            url:'https://www.easy-mock.com/mock/5b7d2254a553b04aa3c93015/example/mock',
            method: 'get',
        }).then(result => {
            console.log(result)
        })
    }
}

export default new Vuex.Store({
    state,
    mutations
})
