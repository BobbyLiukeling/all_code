import * as types from './mutation-types';




export default {
    [types.receve_userInfo] (state, {res} ) {
        state.userInfo.name = res.data.name
        state.userInfo.msg = res.data.msg
        state.userInfo.city = res.data.city
        state.userInfo.imgUrl = res.data.imgUrl
    }
}




























