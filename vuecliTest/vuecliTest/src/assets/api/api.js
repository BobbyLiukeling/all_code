import axios from 'axios'


const api_hostname = './api'
let host = 'https://www.easy-mock.com/mock/5b4b061fbd16ee05c6e4463f/example';

//登录
export const login_url = `${api_hostname}/login`
//验证码
export const yanzhengma_url = `${api_hostname}/identify`
//注册
export const register_url = `${api_hostname}/register`




//获取热门文章
export const hotEssay = params => {
    return axios.get(`${host}/hotEssay/`)
  }

//获取轮播图
export const lunbo = params => {
    return axios.get(`${host}/span/`)
  }

//获取热门分类
export const hotClass = params => {
    return axios.get(`${host}/list/`)
  }
//初始化用户信息
export const initUserData = params => {
  return axios.post(`${host}/initUserData/`, params)
}
//获取历史记录
export const history = params => {
  return axios.get(`${host}/history/`, params)
}




