import Vue from 'vue'
import Vuex from 'vuex';

import getters from './getter'
import mutations from './mutation'
import actions from './action'


Vue.use(Vuex);


import cookie from '../assets/cookie'

//此处为了做测试，后期删除
// cookie.setCookie()
var id = 12
var token = '45678'
var city = '成都市'
cookie.setCookie( id, token, city )

const userInfo = {
    name: '',
    id : cookie.getCookie().userId,
    token : cookie.getCookie().token,
    city : cookie.getCookie().city,
    imgUrl : '',
    qianming : '',
    msg : 23,
}



const state = {
    userInfo
}


export default new Vuex.Store({
    state,
    mutations,
    getters,
    actions
})








