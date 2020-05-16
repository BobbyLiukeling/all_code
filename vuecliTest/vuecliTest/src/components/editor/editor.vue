<template>
    <div class="editor" >
        <Affix :offset-top="50" class="left">
        <div id="toolbar">
            <Tooltip content="字体大小" placement="right" :delay='400'>
                <span class="ql-formats"><select class="ql-size">
                    <option value="small"></option>
                    <option selected></option>
                    <option value="large"></option>
                    <option value="huge"></option>
                </select></span>
            </Tooltip>
            <Tooltip content="对齐" placement="right" :delay='400'>
                <span class="ql-formats">
                    <select class="ql-align">
                        <option selected="selected"></option>
                        <option value="center"></option>
                        <option value="right"></option>
                        <option value="justify"></option>
                    </select>
                </span>
            </Tooltip>
            <Tooltip v-for="(item,index) in iconList"  :content=item.content placement="right" :delay='400'>
                <Button :class="item.class" />
            </Tooltip>
            <Tooltip v-for="(item,index) in hasValue"  :content=item.content placement="right" :delay='400'>
                <Button :class="item.class" :value="item.value" />
            </Tooltip>
            <Tooltip content="字体颜色" placement="right" :delay='400'>
                <span class="ql-formats"><select class="ql-color">
                        <option selected="selected"></option>
                        <option value="#e60000"></option>
                        <option value="#ff9900"></option>
                        <option value="#ffff00"></option>
                        <option value="#008a00"></option>
                        <option value="#0066cc"></option>
                        <option value="#9933ff"></option>
                        <option value="#ffffff"></option>
                        <option value="#facccc"></option>
                        <option value="#ffebcc"></option>
                        <option value="#ffffcc"></option>
                        <option value="#cce8cc"></option>
                        <option value="#cce0f5"></option>
                        <option value="#ebd6ff"></option>
                        <option value="#bbbbbb"></option>
                        <option value="#f06666"></option>
                        <option value="#ffc266"></option>
                        <option value="#ffff66"></option>
                        <option value="#66b966"></option>
                        <option value="#66a3e0"></option>
                        <option value="#c285ff"></option>
                        <option value="#888888"></option>
                        <option value="#a10000"></option>
                        <option value="#b26b00"></option>
                        <option value="#b2b200"></option>
                        <option value="#006100"></option>
                        <option value="#0047b2"></option>
                        <option value="#6b24b2"></option>
                        <option value="#444444"></option>
                        <option value="#5c0000"></option>
                        <option value="#663d00"></option>
                        <option value="#666600"></option>
                        <option value="#003700"></option>
                        <option value="#002966"></option>
                        <option value="#3d1466"></option>
                    </select></span>
            </Tooltip>
            <Tooltip content="字体背景颜色" placement="right" :delay='400'>
                     <span class="ql-formats"> <select class="ql-background">
                        <option value="#000000"></option>
                        <option value="#e60000"></option>
                        <option value="#ff9900"></option>
                        <option value="#ffff00"></option>
                        <option value="#008a00"></option>
                        <option value="#0066cc"></option>
                        <option value="#9933ff"></option>
                        <option selected="selected"></option>
                        <option value="#facccc"></option>
                        <option value="#ffebcc"></option>
                        <option value="#ffffcc"></option>
                        <option value="#cce8cc"></option>
                        <option value="#cce0f5"></option>
                        <option value="#ebd6ff"></option>
                        <option value="#bbbbbb"></option>
                        <option value="#f06666"></option>
                        <option value="#ffc266"></option>
                        <option value="#ffff66"></option>
                        <option value="#66b966"></option>
                        <option value="#66a3e0"></option>
                        <option value="#c285ff"></option>
                        <option value="#888888"></option>
                        <option value="#a10000"></option>
                        <option value="#b26b00"></option>
                        <option value="#b2b200"></option>
                        <option value="#006100"></option>
                        <option value="#0047b2"></option>
                        <option value="#6b24b2"></option>
                        <option value="#444444"></option>
                        <option value="#5c0000"></option>
                        <option value="#663d00"></option>
                        <option value="#666600"></option>
                        <option value="#003700"></option>
                        <option value="#002966"></option>
                        <option value="#3d1466"></option>
                </select></span>
            </Tooltip>
            <Tooltip content="回退" placement="right" :delay='400'>
                <Icon type="ios-undo" @click="undo" size='18' />
            </Tooltip>
            <Tooltip content="前进" placement="right" :delay='400' class="redo">
                <Icon type="ios-redo" @click="redo" size='18' />
            </Tooltip>
        </div>
        </Affix>
        <div class="right">
            <input type="text" class="title" placeholder="标题..." />
            <vue-editor id="qwe"
            v-model="content"
                ref="ee"
                :customModules="customModulesForEditor"
                :editorOptions="editorSettings"
                useCustomImageHandler
                @imageAdded="handleImageAdded"
                />
        </div>
    </div>
</template>

<script>

const iconList = [
    {
        content : '加粗',
        class : 'ql-bold'
    },
    {
        content : '斜体',
        class : 'ql-italic'
    },
    {
        content : '下划线',
        class : 'ql-underline'
    },
    {
        content : '删除线',
        class : 'ql-strike'
    },
    {
        content : '引用',
        class : 'ql-blockquote'
    },
    {
        content : '代码块',
        class : 'ql-code-block'
    },
    {
        content : '清除文本格式',
        class : 'ql-clean'
    },
    {
        content : '链接',
        class : 'ql-link'
    },
    {
        content : '插入图片',
        class : 'ql-image'
    },
]

const hasValue = [
    {
        content : '标题1',
        class : 'ql-header',
        value : '1'
    },
    {
        content : '标题2',
        class : 'ql-header',
        value : '2'
    },
    {
        content : '有序列表',
        class : 'ql-list',
        value : 'ordered'
    },
    {
        content : '无序列表',
        class : 'ql-list',
        value : 'bullet'
    },
    {
        content : '下标',
        class : 'ql-script',
        value : 'sub'
    },
    {
        content : '上标',
        class : 'ql-script',
        value : 'super'
    },
    {
        content : '左缩进',
        class : 'ql-indent',
        value : '-1'
    },
    {
        content : '右缩进',
        class : 'ql-indent',
        value : '+1'
    },
    {
        content : '左右对齐',
        class : 'ql-direction',
        value : 'rtl'
    }
]
import { VueEditor , Quill} from 'vue2-editor'
import ImageResize from 'quill-image-resize-module'
import 'quill/dist/quill.snow.css'
import ImageCompressor from 'image-compressor.js'
export default {
    components: {
        VueEditor
    },
    data(){
        return{
            color4: '#19be6b',
            iconList,
            hasValue,
            content: '正文......',
            customModulesForEditor: [
                { alias: 'imageResize', module: ImageResize },
            ],
            editorSettings: {
                theme: 'snow',
                modules: {
                    toolbar: '#toolbar',
                    imageResize: {
                        modules: ["DisplaySize", "Toolbar", "Resize"]
                    },
                    history: {
                        delay: 2000,
                        maxStack: 500,
                        userOnly: true
                    }
                }
            }
        }
    },
    methods:{
        handleImageAdded: function(file, Editor, cursorLocation, resetUploader) {
        if(file.size > 1024*1024*2){
            new ImageCompressor(file,{
                quality : .7,
                success(result){
                    var formData = new FormData();
                    formData.append('file', result, result.name);
                    console.log(result)
                }
            })
        }else{
            var formData = new FormData();
            formData.append('image', file)
        }
        this.axios({
            url: ' https://www.easy-mock.com/mock/5b4b061fbd16ee05c6e4463f/example/upload',
            method: 'POST',
            data: formData
        })
        .then((result) => {
            let url = result.data.data.url // Get url from response
            Editor.insertEmbed(cursorLocation, 'image', url);
            //   resetUploader();
        })
        .catch((err) => {
            console.log(err);
        })
      },
      undo(){
        this.$refs.ee.quill.history.undo()
      },
      redo(){
        this.$refs.ee.quill.history.redo()
      },
    }
}
</script>

<style scoped>
#toolbar{
    margin: 0 auto;
    display: flex;
    flex-direction: column;
    border: none!important;
    z-index: 99;
    text-align: left;
}
.left{
    width: 10%;
    position: relative;
    top: 40px;
}
.editor{
    max-width: 1050px;
    margin: 0 auto;
    display: flex;
    justify-content: space-between;
}
.redo{
    padding-left: 12px;
}
.right{
    width: 80%;
    padding-top: 20px;
}
.title{
    border: none;
    width: 100%;
    height: 80px;
    font-size: 40px;
    font-weight: bold;
}
</style>
<style>
.ql-picker{
    top: -3px!important;
}
.ql-editor{
    max-width: 1050px;
    margin: 0 auto;
    border: none!important;
}
.ql-snow{
    border: none!important;
}
</style>

