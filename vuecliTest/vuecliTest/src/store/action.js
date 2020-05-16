import * as types from './mutation-types';


import { initUserData } from '../assets/api/api'


import cookie from '../assets/cookie';


export default {
    initUser ({commit}) {
        if(cookie.getCookie().userId){
            var user = {}
            user.id = cookie.getCookie().userId
            user.token = cookie.getCookie().Token
            initUserData(user)
            .then(res => {
                commit(types.receve_userInfo, {res})
            })
        }
    }
}


















