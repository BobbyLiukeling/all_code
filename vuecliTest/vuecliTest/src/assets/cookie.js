




var cookie = {
    setCookie( id, token, name, city){
        var exdate = new Date()
        var user = {
            userId : id,
            userToken :token,
            userCity :city
        }
        var d = JSON.stringify(user)
        window.localStorage.setItem('userData',d)
    },
    getCookie(){
        var json = window.localStorage.getItem("userData")
        var userInfo = JSON.parse(json)
        return userInfo
    },
    delCookie(){
        window.localStorage.removeItem('userData')
    }
}

export default cookie























