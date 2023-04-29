// ==UserScript==
// @name         XMOJ
// @version      0.1
// @description  Test
// @author       @langningchen
// @match        http://www.xmoj.tech/*
// @icon         https://www.google.com/s2/favicons?sz=64&domain=xmoj.tech
// @require      https://cdn.bootcdn.net/ajax/libs/jszip/3.10.1/jszip.min.js
// @grant        none
// ==/UserScript==

let QuestionSize = 0;
let AddedSubmissionCount = 0;
let ProgressBar = null;
let SubmitRecord = null;
(function() {
    "use strict";

    let Discuss = document.createElement("li");
    document.querySelector("#navbar > ul:nth-child(1)").appendChild(Discuss);
    Discuss.innerHTML = "<a href=\"./bbs.php\">讨论</a>";
    if (document.querySelector("#navbar > ul:nth-child(1)").childElementCount > 8) {
        let ACMRank = document.createElement("li");
        document.querySelector("#navbar > ul:nth-child(1)").insertBefore(ACMRank, document.querySelector("#navbar > ul:nth-child(1) > li:nth-child(9)"));
        ACMRank.innerHTML = "<a href=\"./contestrank-oi.php?" + location.href.substr(location.href.indexOf("cid=")) + "&ByUserScript=1\">ACM 排名</a>";
        ACMRank.classList.add("active");
    }
    document.querySelector("#navbar > ul:nth-child(1) > li:nth-child(2) > a").innerText = "题库";

    if (location.href.indexOf("/comparesource.php?") == -1) {
        document.body.innerHTML =
            String(document.body.innerHTML).replaceAll(
                /\[<a href="([^"]*)">([^<]*)<\/a>\]/g,
                "<button onclick=\"location.href='$1'\" class=\"UserScriptDefinedButton\">$2</button>");
        document.body.innerHTML = String(document.body.innerHTML).replaceAll("小明", "高老师");
        document.body.innerHTML = String(document.body.innerHTML).replaceAll("下海", "上海");
        document.title = String(document.title).replaceAll("小明", "高老师");
    } else {
        let CheckboxLable = document.createElement("label");
        document.querySelector("body > div.container > div > table:nth-child(2) > tbody > tr > td").appendChild(CheckboxLable);
        CheckboxLable.innerText = "忽略空白";
        CheckboxLable.setAttribute("for", "ignorews");
        document.querySelector("body > div.container > div > table:nth-child(2) > tbody > tr > td").childNodes[1].remove();
    }

    var Style = document.createElement("style");
    document.body.appendChild(Style);
    Style.innerHTML = "";
    Style.innerHTML += "marquee {";
    Style.innerHTML += "  display: none !important;";
    Style.innerHTML += "}";

    Style.innerHTML += ".pagination, .form-control, .status, .test-case {";
    Style.innerHTML += "  transition: 0.5s !important;";
    Style.innerHTML += "}";
    Style.innerHTML += ".form-control:hover {";
    Style.innerHTML += "  border-color: #428bca !important;";
    Style.innerHTML += "}";
    Style.innerHTML += ".form-control[type=submit] {";
    Style.innerHTML += "  margin-right: 15px !important;";
    Style.innerHTML += "}";
    Style.innerHTML += ".form-control[type=submit]:hover {";
    Style.innerHTML += "  background-color: #428bca !important;";
    Style.innerHTML += "  color: white !important;";
    Style.innerHTML += "}";
    Style.innerHTML += ".status_y:hover {";
    Style.innerHTML += "  box-shadow: #52c41a 1px 1px 10px 0px !important;";
    Style.innerHTML += "}";
    Style.innerHTML += ".status_n:hover {";
    Style.innerHTML += "  box-shadow: #fe4c61 1px 1px 10px 0px !important;";
    Style.innerHTML += "}";
    Style.innerHTML += ".red {";
    Style.innerHTML += "  color: red !important;";
    Style.innerHTML += "}";
    Style.innerHTML += ".green {";
    Style.innerHTML += "  color: green !important;";
    Style.innerHTML += "}";
    Style.innerHTML += ".blue {";
    Style.innerHTML += "  color: blue !important;";
    Style.innerHTML += "}";
    Style.innerHTML += ".UserScriptDefinedButton {";
    Style.innerHTML += "  display: inline-block;"
    Style.innerHTML += "  height: 34px;"
    Style.innerHTML += "  padding: 6px 12px;"
    Style.innerHTML += "  font-size: 14px;"
    Style.innerHTML += "  line-height: 1.42857143;"
    Style.innerHTML += "  color: #555;"
    Style.innerHTML += "  background-color: #fff;"
    Style.innerHTML += "  background-image: none;"
    Style.innerHTML += "  border: 1px solid #ccc;"
    Style.innerHTML += "  border-radius: 4px;"
    Style.innerHTML += "  box-shadow: inset 0 1px 1px rgba(0,0,0,.075);"
    Style.innerHTML += "  transition: 0.5s;";
    Style.innerHTML += "  margin-right: 5px;";
    Style.innerHTML += "}";
    Style.innerHTML += ".UserScriptDefinedButton:hover {";
    Style.innerHTML += "  background-color: #428bca !important;";
    Style.innerHTML += "  color: white !important;";
    Style.innerHTML += "}";
    Style.innerHTML += ".btn-info {";
    Style.innerHTML += "  cursor: default !important;";
    Style.innerHTML += "}";
    Style.innerHTML += ".btn {";
    Style.innerHTML += "  margin-right: 5px !important;";
    Style.innerHTML += "}";
    Style.innerHTML += ".test-case {";
    Style.innerHTML += "  border-radius: 5px !important;";
    Style.innerHTML += "}";
    Style.innerHTML += ".test-case:hover {";
    Style.innerHTML += "  box-shadow: rgba(0, 0, 0, 0.3) 0px 10px 20px 3px !important;";
    Style.innerHTML += "}";
    Style.innerHTML += ".badge-info {";
    Style.innerHTML += "  background-color: lightgray !important;";
    Style.innerHTML += "}";
    Style.innerHTML += ".badge {";
    Style.innerHTML += "  margin: 2px !important;";
    Style.innerHTML += "  border-radius: 7px !important;";
    Style.innerHTML += "  min-width: 25px !important;";
    Style.innerHTML += "}";
    Style.innerHTML += "input[type=checkbox] {";
    Style.innerHTML += "  position: absolute;";
    Style.innerHTML += "  clip: rect(0, 0, 0, 0);";
    Style.innerHTML += "}";
    Style.innerHTML += "input[type=checkbox] + label::before {";
    Style.innerHTML += "  content: \"\\a0\";";
    Style.innerHTML += "  display: inline-block;";
    Style.innerHTML += "  vertical-align: 2px;";
    Style.innerHTML += "  width: 14px;";
    Style.innerHTML += "  height: 14px;";
    Style.innerHTML += "  margin-right: 5px;";
    Style.innerHTML += "  border-radius: 3px;";
    Style.innerHTML += "  text-indent: 2px;";
    Style.innerHTML += "  line-height: .65;";
    Style.innerHTML += "  cursor: pointer;";
    Style.innerHTML += "  background-color: #fe4c61;";
    Style.innerHTML += "}";
    Style.innerHTML += "input[type=checkbox]:checked + label::before {";
    Style.innerHTML += "  content: \"\\2713\";";
    Style.innerHTML += "  background-color: #52c41a;";
    Style.innerHTML += "}";

    if (location.href.indexOf("/problemset.php") != -1) {
        document.querySelector("body > div > div > center > table:nth-child(2) > tbody > tr > td:nth-child(2) > form > input").placeholder = "题目编号";
        document.querySelector("body > div > div > center > table:nth-child(2) > tbody > tr > td:nth-child(2) > form > button").innerText = "确认";
        document.querySelector("body > div > div > center > table:nth-child(2) > tbody > tr > td:nth-child(3) > form > input").placeholder = "标题或内容";
        document.querySelector("#problemset > thead > tr > th:nth-child(1)").innerText = "状态";
    } else if (location.href.indexOf("/problem.php") != -1) {
        document.getElementsByTagName("center")[1].style.display = "none";
        $(".copy-btn").click(function() {
            const span = $(this).next().find(".sampledata");
            if (!span.length) {
                $(this).text("未找到pre").addClass("done");
                setTimeout(function() {
                    $(".copy-btn").text("复制").removeClass("done");
                }, 1000);
                return;
            }
            const textarea = $("<textarea></textarea>").attr("readonly", "readonly").text(span.text());
            document.body.appendChild(textarea[0]);
            textarea.select();
            if (document.execCommand("copy")) {
                $(this).text("复制成功").addClass("done");
                setTimeout(function() {
                    $(".copy-btn").text("复制").removeClass("done");
                }, 1000);
            }
            document.body.removeChild(textarea[0]);
        });
        let DiscussButton = document.createElement("button");
        document.querySelector("body > div.container > div > center").appendChild(DiscussButton);
        DiscussButton.className = "UserScriptDefinedButton";
        DiscussButton.innerText = "讨论";
        DiscussButton.onclick = function() {
            window.open("http://www.xmoj.tech/discuss3/discuss.php?p" + location.href.substring(location.href.indexOf("id=")));
        };
    } else if (location.href.indexOf("/status.php") != -1) {
        document.querySelector("#simform > input:nth-child(2)").style.display = "none";
        document.querySelector("#simform").innerHTML = document.querySelector("#simform").innerHTML.replaceAll("用户:", "");
        document.querySelector("#simform").innerHTML = document.querySelector("#simform").innerHTML.replaceAll(":", ": ");
        document.querySelector("#simform").style.paddingBottom = "7px";
        let CompareButton = document.createElement("button");
        document.querySelector("body > div.container > div > div.input-append").appendChild(CompareButton);
        CompareButton.className = "UserScriptDefinedButton";
        CompareButton.innerText = "比较提交记录";
        CompareButton.onclick = function() {
            location.href = "comparesource.php";
        };
        CompareButton.style.marginBottom = "7px";

        document.querySelector("#result-tab > thead > tr > th:nth-child(1)").style.display = "none";
        document.querySelector("#result-tab > thead > tr > th:nth-child(3)").style.display = "none";
        document.querySelector("#result-tab > thead > tr > th:nth-child(11)").style.display = "none";
        document.querySelector("#result-tab > thead > tr > th:nth-child(12)").style.display = "none";
        var Temp = document.querySelector("#result-tab > tbody").childNodes;
        for (let i = 1; i < Temp.length; i += 2) {
            Temp[i].childNodes[0].style.display = "none";
            Temp[i].childNodes[1].innerHTML = "<a href=\"showsource.php?id=" + Temp[i].childNodes[1].innerText + "\">" + Temp[i].childNodes[1].innerText + "</a>";
            Temp[i].childNodes[2].style.display = "none";
            Temp[i].childNodes[7].innerText = Temp[i].childNodes[7].childNodes[0].innerText;
            let Memory = parseInt(Temp[i].childNodes[5].childNodes[0].innerText);
            let StringMemory = "";
            if (Memory < 1024) {
                StringMemory = Memory + "B";
            } else if (Memory < 1024 * 1024) {
                StringMemory = (Memory / 1024).toFixed(2) + "KB";
            } else if (Memory < 1024 * 1024) {
                StringMemory = (Memory / 1024 / 1024).toFixed(2) + "MB";
            } else {
                StringMemory = (Memory / 1024 / 1024 / 1024).toFixed(2) + "GB";
            }
            Temp[i].childNodes[5].childNodes[0].innerText = StringMemory;
            let Time = parseInt(Temp[i].childNodes[6].childNodes[0].innerText);
            let StringTime = "";
            if (Time < 1000) {
                StringTime = Time + "ms";
            } else {
                StringTime = (Time / 1000).toFixed(2) + "s";
            }
            Temp[i].childNodes[6].childNodes[0].innerText = StringTime;
            let Length = parseInt(String(Temp[i].childNodes[8].innerText).substr(0, String(Temp[i].childNodes[8].innerText).length - 2));
            let StringLength = "";
            if (Length < 1024) {
                StringLength = Length + "B";
            } else {
                StringLength = (Length / 1024).toFixed(2) + "KB";
            }
            Temp[i].childNodes[8].innerText = StringLength;
            Temp[i].childNodes[10].style.display = "none";
            Temp[i].childNodes[11].style.display = "none";
        }

        document.querySelector("#result-tab > tbody").innerHTML =
            String(document.querySelector("#result-tab > tbody").innerHTML).replaceAll("class=\"center\"", "");
    } else if (location.href.indexOf("/contest.php") != -1) {
        clock = function() {
            function ClockTick() {
                let CurrentDate = new Date(new Date().getTime() + diff);
                let Year = CurrentDate.getFullYear();
                if (Year > 3000) {
                    Year -= 1900;
                }
                let Month = CurrentDate.getMonth() + 1;
                let _Date = CurrentDate.getDate();
                let Hours = CurrentDate.getHours();
                let Minutes = CurrentDate.getMinutes();
                let Seconds = CurrentDate.getSeconds();
                document.getElementById("nowdate").innerHTML =
                    Year + "-" +
                    (Month < 10 ? "0" : "") + Month + "-" +
                    (_Date < 10 ? "0" : "") + _Date + " " +
                    (Hours < 10 ? "0" : "") + Hours + ":" +
                    (Minutes < 10 ? "0" : "") + Minutes + ":" +
                    (Seconds < 10 ? "0" : "") + Seconds;
            }
            setInterval(ClockTick, 200);
        }
        if (location.href.indexOf("?cid=") == -1) {
            document.querySelector("body > div > div > center").innerHTML =
                String(document.querySelector("body > div > div > center").innerHTML).replaceAll("ServerTime:", "服务器时间：");
            document.querySelector("body > div > div > center > table").style.marginTop = "10px";
            document.querySelector("body > div > div > center > form").style.display = "none";
            document.querySelector("body > div > div > center > table > thead > tr").childNodes[0].innerText = "编号";
            document.querySelector("body > div > div > center > table > thead > tr").childNodes[1].innerText = "标题";
            document.querySelector("body > div > div > center > table > thead > tr").childNodes[2].innerText = "状态";
            document.querySelector("body > div > div > center > table > thead > tr").childNodes[3].innerText = "私有";
            document.querySelector("body > div > div > center > table > thead > tr").childNodes[4].innerText = "创建者";
            Temp = document.querySelector("body > div > div > center > table > tbody").childNodes;
            for (let i = 1; i < Temp.length; i++) {
                var CurrentElement = Temp[i].childNodes[2].childNodes;
                if (CurrentElement[1].childNodes[0].data.indexOf("运行中") != -1) {
                    let Time = String(CurrentElement[1].childNodes[1].innerText).substr(4);
                    let Day = parseInt(Time.substring(0, Time.indexOf("天")));
                    let Hour = parseInt(Time.substring(Time.indexOf("天") + 1, Time.indexOf("小时")));
                    let Minute = parseInt(Time.substring(Time.indexOf("小时") + 2, Time.indexOf("分")));
                    let Second = parseInt(Time.substring(Time.indexOf("分") + 1, Time.indexOf("秒")));
                    let TimeStamp = new Date().getTime() + diff + (((Day * 24 + Hour) * 60 + Minute) * 60 + Second) * 1000;
                    CurrentElement[1].childNodes[1].setAttribute("EndTime", TimeStamp);
                    CurrentElement[1].childNodes[1].classList.add("UpdateByJS");
                } else if (CurrentElement[1].childNodes[0].data.indexOf("开始于") != -1) {
                    let TimeStamp = Date.parse(String(CurrentElement[1].childNodes[0].data).substr(4)) - diff;
                    console.log(CurrentElement[1].childNodes[0].data, TimeStamp);
                    CurrentElement[1].setAttribute("EndTime", TimeStamp);
                    CurrentElement[1].classList.add("UpdateByJS");
                } else if (CurrentElement[1].childNodes[0].data.indexOf("已结束") != -1) {
                    let TimeStamp = String(CurrentElement[1].childNodes[0].data).substr(4);
                    CurrentElement[1].childNodes[0].data = " 已结束 ";
                    CurrentElement[1].className = "red";
                    let Temp = document.createElement("span");
                    CurrentElement[1].appendChild(Temp);
                    Temp.className = "green";
                    Temp.innerHTML = TimeStamp;
                }
                Temp[i].childNodes[4].innerHTML = "<a href=\"userinfo.php?user=" + Temp[i].childNodes[4].innerHTML + "\">" + Temp[i].childNodes[4].innerHTML + "</a>";
            }

            function UpdateJS() {
                Temp = document.getElementsByClassName("UpdateByJS");
                for (let i = 0; i < Temp.length; i++) {
                    let TimeStamp = parseInt(Temp[i].getAttribute("EndTime"));
                    TimeStamp = TimeStamp - new Date().getTime() - diff;
                    if (TimeStamp < 0) {
                        window.location.reload();
                    }
                    let CurrentDate = new Date(TimeStamp);
                    let Day = parseInt(TimeStamp / 1000 / 60 / 60 / 24);
                    let Hour = CurrentDate.getUTCHours();
                    let Minute = CurrentDate.getUTCMinutes();
                    let Second = CurrentDate.getUTCSeconds();
                    Temp[i].innerText = (Day != 0 ? Day + "天" : "") +
                        (Hour < 10 ? "0" : "") + Hour + ":" +
                        (Minute < 10 ? "0" : "") + Minute + ":" +
                        (Second < 10 ? "0" : "") + Second;
                }
            }
            setInterval(UpdateJS, 200);
        } else {
            document.querySelector("body > div > div > center > br:nth-child(2)").remove();
            document.querySelector("body > div > div > center > br:nth-child(2)").remove();
            document.querySelector("body > div > div > center > div > span:nth-child(9)").innerHTML =
                String(document.querySelector("body > div > div > center > div > span:nth-child(9)").innerHTML).replaceAll("<br>", "<br><br>");
            let HTMLData = document.querySelector("body > div > div > center > div").innerHTML;
            HTMLData = HTMLData.replaceAll("&nbsp;&nbsp;\n&nbsp;&nbsp;", "&nbsp;")
            HTMLData = HTMLData.replaceAll("<br>开始于: ", "开始时间：")
            HTMLData = HTMLData.replaceAll("\n结束于: ", "<br>结束时间：")
            HTMLData = HTMLData.replaceAll("\n现在时间: ", "当前时间：")
            HTMLData = HTMLData.replaceAll("\n状态:", "<br>状态：")
            document.querySelector("body > div > div > center > div").innerHTML = HTMLData;
            let StaticButton = document.createElement("button");
            document.querySelector("body > div > div > center > div > span:nth-child(10)").appendChild(StaticButton);
            StaticButton.classList.add("UserScriptDefinedButton");
            StaticButton.innerText = "统计";
            StaticButton.onclick = function() {
                location.href = "/conteststatistics.php" + location.href.substr(location.href.indexOf("?cid="));
            };

            document.querySelector("#problemset > tbody").innerHTML =
                String(document.querySelector("#problemset > tbody").innerHTML).replaceAll(
                    /\t&nbsp;([0-9]*) &nbsp;&nbsp;&nbsp;&nbsp; 问题 &nbsp;([^<]*)/g,
                    "$2. $1");

            document.querySelector("#problemset > tbody").innerHTML =
                String(document.querySelector("#problemset > tbody").innerHTML).replaceAll(
                    /\t\*([0-9]*) &nbsp;&nbsp;&nbsp;&nbsp; 问题 &nbsp;([^<]*)/g,
                    "<del>$2. $1</del>");

            if (document.querySelector("#problemset > thead > tr > td:nth-child(4)") != null) {
                document.querySelector("#problemset > thead > tr > td:nth-child(4)").style.display = "none";
                let Temp = document.querySelector("#problemset > tbody").childNodes;
                for (let i = 1; i < Temp.length; i++) {
                    Temp[i].childNodes[3].style.display = "none";
                }
            }

            document.querySelector("#problemset > thead > tr > td:nth-child(1)").innerText = "状态";
        }
    } else if (location.href.indexOf("/contestrank-oi.php") != -1) {
        if (document.getElementById("rank") == null) {
            document.body.innerHTML = "";
            let NewURL = new URL(location.href);
            NewURL.pathname = "/contestrank2.php";
            let Show = document.createElement("iframe");
            document.body.appendChild(Show);
            Show.src = NewURL.toString();
            Show.style.width = "100%";
            Show.style.height = "100%";
            Show.style.border = "none";
        } else if (new URL(location.href).searchParams.get("ByUserScript") != null) {
            document.getElementById("rank").style.width = "100%";
            document.querySelector("body > div.container > div > center").style.paddingBottom = "10px";
            document.querySelector("body > div.container > div > center > a").style.display = "none";
            let DownloadButton = document.createElement("button");
            document.querySelector("body > div.container > div > center").appendChild(DownloadButton);
            DownloadButton.classList.add("UserScriptDefinedButton");
            DownloadButton.innerText = "下载排名";
            DownloadButton.onclick = function() {
                let NewURL = new URL(location.href);
                NewURL.pathname = "/contestrank.xls.php";
                location.href = NewURL.toString();
            };
            ProgressBar = document.createElement("progress");
            ProgressBar.style.marginRight = "10px";
            document.querySelector("body > div.container > div").insertBefore(ProgressBar, document.querySelector("#rank"));
            ReloadRank();
            Style.innerHTML += ".well {";
            Style.innerHTML += "  background-image: none;";
            Style.innerHTML += "  padding: 1px;";
            Style.innerHTML += "}";
            Style.innerHTML += "td {";
            Style.innerHTML += "  white-space: nowrap;";
            Style.innerHTML += "";
            Style.innerHTML += "}";
            Style.innerHTML += ".red {";
            Style.innerHTML += "  background-color: #ffa0a0;";
            Style.innerHTML += "}";
            Style.innerHTML += ".green {";
            Style.innerHTML += "  background-color: #33ff33;";
            Style.innerHTML += "}";
            QuestionSize = document.querySelector("#rank > thead > tr").childNodes.length - 8;
            var ReloadProgress = document.createElement("button");
            ReloadProgress.classList.add("UserScriptDefinedButton");
            ReloadProgress.style.marginRight = "20px";
            ReloadProgress.style.marginBottom = "5px";
            ReloadProgress.innerText = "重新播放动画";
            ReloadProgress.onclick = function() {
                PlaySubmission();
            }
            document.querySelector("body > div.container > div").insertBefore(ReloadProgress, document.querySelector("#rank"));
            var Reload = document.createElement("button");
            Reload.classList.add("UserScriptDefinedButton");
            Reload.innerText = "重新加载排名";
            Reload.onclick = function() {
                ReloadRank();
            }
            document.querySelector("body > div.container > div").insertBefore(Reload, document.querySelector("#rank"));
        }
    } else if (location.href.indexOf("/reinfo.php") != -1) {
        Temp = document.querySelector("#results > div").childNodes;
        for (let i = 1; i < Temp.length; i++) {}
    } else if (location.href.indexOf("contestrank-correct.php") != -1) {
        document.querySelector("body > div.container > div > center > a").style.display = "none";
    } else if (location.href.indexOf("/submitpage.php") != -1) {
        document.querySelector("#enable_O2").checked = true;
        document.querySelector("#frmSolution").childNodes[0].nodeValue = "题目";
        document.querySelector("#language_span").childNodes[0].nodeValue = "语言：";
        document.querySelector("#language").style.marginTop = "10px";
        document.querySelector("#language").style.marginBottom = "10px";
        document.querySelector("#source").classList.add("form-control");
        let CheckInterval = setInterval(function() {
            if (document.querySelector("#edit_area_toggle_reg_syntax\\.js > label") != null) {
                document.querySelector("#EditAreaArroundInfos_source").style.display = "block";
                document.querySelector("#EditAreaArroundInfos_source").style.height = "0px";
                document.querySelector("#edit_area_toggle_reg_syntax\\.js > label").innerText = "使用编辑器";
                clearInterval(CheckInterval);
            }
        }, 100);
        let O2Label = document.createElement("label");
        document.querySelector("#frmSolution").insertBefore(O2Label, document.querySelector("#enable_O2").nextElementSibling);
        O2Label.innerText = "打开O2开关";
        O2Label.setAttribute("for", "enable_O2");
        let Temp = document.querySelector("#frmSolution").childNodes;
        for (let i = 0; i < Temp.length; i++) {
            if (Temp[i].data == "打开O2开关") {
                Temp[i].remove();
                i--;
            } else if (Temp[i].id == "EditAreaArroundInfos_source")
                Temp[i + 1].remove();
            else if (Temp[i].getAttribute != null && Temp[i].getAttribute("for") == "enable_O2") {
                Temp[i + 1].remove();
                Temp[i + 1].remove();
            }
        }
    } else if (location.href.indexOf("/discuss3/discuss.php") != -1) {
        let Temp = document.querySelector("body > div.container > div > center > div > table > tbody").children;
        for (let i = 0; i < Temp.length; i++) {
            Temp[i].children[0].style.display = "none";
            Temp[i].children[1].style.display = "none";
        }
        document.querySelector("body > div.container > div > center > div > div:nth-child(2)").childNodes[0].data = "当前位置：";
        document.querySelector("body > div.container > div > center > div > div:nth-child(2) > a:nth-child(1)").innerText = "主面板";
        document.querySelector("body > div.container > div > center > div > div:nth-child(1) > a").innerText = "发起讨论";
        document.querySelector("body > div.container > div > center > div > table > tbody > tr.toprow > td:nth-child(3)").innerHTML = "题目编号";
        document.querySelector("body > div.container > div > center > div > table > tbody > tr.toprow > td:nth-child(4)").innerHTML = "发起人";
        document.querySelector("body > div.container > div > center > div > table > tbody > tr.toprow > td:nth-child(5)").innerHTML = "标题";
        document.querySelector("body > div.container > div > center > div > table > tbody > tr.toprow > td:nth-child(6)").innerHTML = "发布日期";
        document.querySelector("body > div.container > div > center > div > table > tbody > tr.toprow > td:nth-child(7)").innerHTML = "最后回复";
        document.querySelector("body > div.container > div > center > div > table > tbody > tr.toprow > td:nth-child(8)").innerHTML = "回复数";
        if (document.querySelector("body > div.container > div > center > div > div:nth-child(3) > a") != null) {
            document.querySelector("body > div.container > div > center > div > div:nth-child(3) > a").innerText = "返回题目";
            document.querySelector("body > div.container > div > center > div > div:nth-child(2) > a:nth-child(2)").innerText =
                document.querySelector("body > div.container > div > center > div > div:nth-child(2) > a:nth-child(2)").innerText.
            replaceAll("Problem", "题目");
        }
        if (document.querySelector("body > div.container > div > center > div > table > tbody > tr.evenrow > td:nth-child(2)").innerText == "No thread here.") {
            document.querySelector("body > div.container > div > center > div > table > tbody > tr.evenrow > td:nth-child(2)").innerText = "没有讨论，快来发起讨论吧！";
        }
    } else if (location.href.indexOf("/discuss3/thread.php") != -1) {
        if (document.querySelector("body > div.container > div > center > div > table > tbody > tr.toprow > td > a").innerText.indexOf("Problem") != -1) {
            document.querySelector("body > div.container > div > center > div > table > tbody > tr.toprow > td > a").innerText =
                document.querySelector("body > div.container > div > center > div > table > tbody > tr.toprow > td > a").innerText.
            replaceAll("Problem", "题目");
        } else if (document.querySelector("body > div.container > div > center > div > table > tbody > tr.toprow > td > a").innerText.indexOf("Main") != -1) {
            document.querySelector("body > div.container > div > center > div > table > tbody > tr.toprow > td > a").innerText = "主面板";
        }
        document.querySelector("body > div.container > div > center > div > div:nth-child(1) > a").innerText = "发起讨论";
        let Temp = document.querySelector("body > div.container > div > center > div > table > tbody").children;
        for (let i = 1; i < Temp.length; i++) {
            Temp[i].children[0].children[2].children[0].remove();
            Temp[i].children[0].children[2].children[0].remove();
            Temp[i].children[0].children[2].children[0].remove();
        }
        document.querySelector("body > div.container > div > center > div > div:nth-child(4) > div").innerText = "回复：";
        document.querySelector("body > div.container > div > center > div > form > div:nth-child(2) > textarea").setAttribute("style", "");
        document.querySelector("body > div.container > div > center > div > form > div:nth-child(2) > textarea").classList.add("form-control");
        document.querySelector("body > div.container > div > center > div > form > div:nth-child(3) > input[type=submit]").innerText = "提交";
        document.querySelector("body > div.container > div > center > div > form > div:nth-child(3) > input[type=submit]").classList.add("form-control");
        document.querySelector("body > div.container > div > center > div > form > div:nth-child(3) > input[type=submit]").style.marginLeft = "0px";
        document.querySelector("body > div.container > div > center > div > div:nth-child(3) > button:nth-child(1)").innerText = "返回首页";
        document.querySelector("body > div.container > div > center > div > div:nth-child(3) > button:nth-child(2)").innerText = "前一页";
        document.querySelector("body > div.container > div > center > div > div:nth-child(3) > button:nth-child(3)").innerText = "后一页";
    } else if (location.href.indexOf("/discuss3/newpost.php") != -1) {
        document.querySelector("body > div.container > div > center > div > h2").innerText = "发布新的讨论";
        document.querySelector("body > div.container > div > center > div > form > div:nth-child(2)").innerText = "题目编号：";
        document.querySelector("body > div.container > div > center > div > form > div:nth-child(3) > input").setAttribute("style", "");
        document.querySelector("body > div.container > div > center > div > form > div:nth-child(3) > input").classList.add("form-control");
        document.querySelector("body > div.container > div > center > div > form > div:nth-child(4)").innerText = "标题";
        document.querySelector("body > div.container > div > center > div > form > div:nth-child(5) > input").setAttribute("style", "");
        document.querySelector("body > div.container > div > center > div > form > div:nth-child(5) > input").classList.add("form-control");
        document.querySelector("body > div.container > div > center > div > form > div:nth-child(6)").innerText = "内容";
        document.querySelector("body > div.container > div > center > div > form > div:nth-child(7) > textarea").setAttribute("style", "");
        document.querySelector("body > div.container > div > center > div > form > div:nth-child(7) > textarea").classList.add("form-control");
        document.querySelector("body > div.container > div > center > div > form > div:nth-child(8) > input[type=submit]").value = "提交";
        document.querySelector("body > div.container > div > center > div > form > div:nth-child(8) > input[type=submit]").classList.add("form-control");
        document.querySelector("body > div.container > div > center > div > form > div:nth-child(8) > input[type=submit]").style.marginLeft = "0px";
    } else if (location.href.indexOf("modifypage.php") != -1) {
        document.querySelector("body > div.container > div > form > center > table > tbody > tr:nth-child(1) > td").innerText = "修改账号";
        for (let i = 3; i <= 12; i++) {
            document.querySelector("body > div.container > div > form > center > table > tbody > tr:nth-child(" + i + ") > td:nth-child(2) > input").classList.add("form-control");
            document.querySelector("body > div.container > div > form > center > table > tbody > tr:nth-child(" + i + ") > td:nth-child(2) > input").style.marginBottom = "5px";
        }
        document.querySelector("body > div.container > div > form > center > table > tbody > tr:nth-child(2) > td:nth-child(1)").innerText = "用户ID";
        let Temp = document.querySelector("body > div.container > div > form > center > table > tbody > tr:nth-child(13) > td:nth-child(2) > input:nth-child(1)");
        Temp.classList.add("form-control");
        Temp.style.width = "40%";
        Temp.style.display = "inline-block";
        Temp.value = "修改";
        Temp = document.querySelector("body > div.container > div > form > center > table > tbody > tr:nth-child(13) > td:nth-child(2) > input:nth-child(2)");
        Temp.classList.add("form-control");
        Temp.style.width = "40%";
        Temp.style.display = "inline-block";
        Temp.value = "重置";
        document.querySelector("body > div.container > div > form > center > table > tbody > tr:nth-child(13) > td:nth-child(2)").childNodes[1].remove();
        document.querySelector("body > div.container > div > form > a").remove();
        let ExportACCode = document.createElement("button");
        document.querySelector("body > div.container > div").appendChild(ExportACCode);
        ExportACCode.innerText = "导出AC代码";
        ExportACCode.classList.add("UserScriptDefinedButton");
        ExportACCode.onclick = function() {
            let ExportProgressBar = document.getElementsByTagName("progress")[0] || document.createElement("progress");
            ExportProgressBar.removeAttribute("value");
            ExportProgressBar.removeAttribute("max");
            document.querySelector("body > div.container > div").appendChild(ExportProgressBar);
            ExportACCode.innerText = "正在导出...";
            let Request = new XMLHttpRequest();
            Request.onreadystatechange = function() {
                if (Request.readyState == 4) {
                    if (Request.status == 200) {
                        let Response = Request.responseText;
                        let ACCode = Response.split("------------------------------------------------------\r\n");
                        var Zip = new JSZip();
                        ExportProgressBar.max = ACCode.length - 1;
                        for (let i = 0; i < ACCode.length; i++) {
                            let CurrentCode = ACCode[i];
                            if (CurrentCode == "") {
                                continue;
                            }
                            let CurrentQuestionID = CurrentCode.substr(7, 4);
                            CurrentCode = CurrentCode.substr(14);
                            Zip.file(CurrentQuestionID + ".cpp", CurrentCode);
                            ExportProgressBar.value = i + 1;
                        }
                        Zip.generateAsync({ type: "blob" })
                            .then(function(content) {
                                var CurrentBlob = new Blob([content], { type: "application/zip" });
                                var CurrentURL = URL.createObjectURL(CurrentBlob);
                                var CurrentLink = document.createElement("a");
                                CurrentLink.href = CurrentURL;
                                CurrentLink.download = "AC代码.zip";
                                CurrentLink.click();
                                ExportACCode.innerText = "导出成功";
                            });
                    } else {
                        ExportACCode.innerText = "导出失败";
                    }
                }
            }
            Request.open("GET", "http://www.xmoj.tech/export_ac_code.php", true);
            Request.send();
        }
    } else if (location.href.indexOf("/userinfo.php") != -1) {
        let Temp = document.getElementById("submission").childNodes;
        for (let i = 0; i < Temp.length; i++) {
            Temp[i].remove();
        }
        eval(document.querySelector("body > script:nth-child(6)").innerHTML);
    } else if (location.href.indexOf("/conteststatistics.php") != -1) {
        let Temp = document.getElementById("submission").childNodes;
        for (let i = 0; i < Temp.length; i++) {
            Temp[i].remove();
        }
        eval(document.querySelector("body > div.container > div > center > table:nth-child(4) > script:nth-child(7)").innerHTML);
        document.querySelector("#cs > thead > tr > th:nth-child(1)").innerText = "题目编号";
        document.querySelector("#cs > thead > tr > th:nth-child(10)").style.display = "none";
        document.querySelector("#cs > thead > tr > th:nth-child(12)").innerText = "总和";
        document.querySelector("#cs > thead > tr > th:nth-child(15)").style.display = "none";
        document.querySelector("#cs > tbody > tr:last-child > td").innerText = "总和";
        Temp = document.querySelector("#cs > tbody").children;
        for (let i = 0; i < Temp.length; i++) {
            let Temp2 = Temp[i].children;
            for (let j = 0; j < Temp2.length; j++) {
                if (j == 9 || j == 14) {
                    Temp2[j].style.display = "none";
                }
                if (Temp2[j].innerText == "") {
                    Temp2[j].innerText = "0";
                }
            }
        }
    } else if (location.href.indexOf("/comparesource.php") != -1) {
        document.querySelector("body > div.container > div").innerHTML = "";
        let LeftCodeText = document.createElement("span");
        document.querySelector("body > div.container > div").appendChild(LeftCodeText);
        LeftCodeText.innerText = "左侧代码的运行编号：";
        let LeftCode = document.createElement("input");
        document.querySelector("body > div.container > div").appendChild(LeftCode);
        LeftCode.classList.add("form-control");
        LeftCode.style.width = "40%";
        LeftCode.style.marginBottom = "5px";
        let RightCodeText = document.createElement("span");
        document.querySelector("body > div.container > div").appendChild(RightCodeText);
        RightCodeText.innerText = "右侧代码的运行编号：";
        let RightCode = document.createElement("input");
        document.querySelector("body > div.container > div").appendChild(RightCode);
        RightCode.classList.add("form-control");
        RightCode.style.width = "40%";
        RightCode.style.marginBottom = "5px";
        let CompareButton = document.createElement("button");
        document.querySelector("body > div.container > div").appendChild(CompareButton);
        CompareButton.innerText = "比较";
        CompareButton.classList.add("UserScriptDefinedButton");
        CompareButton.onclick = function() {
            location.href = "/comparesource.php?left=" + LeftCode.value + "&right=" + RightCode.value;
        };
    }

    Temp = document.getElementsByClassName("status_y");
    for (let i = 0; i < Temp.length; i++) {
        Temp[i].innerText = "✓";
    }
    Temp = document.getElementsByClassName("status_n");
    for (let i = 0; i < Temp.length; i++) {
        Temp[i].innerText = "×";
    }

    var LastSortDownList = [];
    var LastSortUpList = [];
    setInterval(function() {
        for (let i = 0; i < LastSortDownList.length; i++) {
            if (LastSortDownList[i].className.indexOf("headerSortDown") == -1) {
                let Text = LastSortDownList[i].innerText;
                Text = Text.substr(0, Text.length - 2);
                LastSortDownList[i].innerText = Text;
                LastSortDownList.splice(i, 1);
            }
        }
        for (let i = 0; i < LastSortUpList.length; i++) {
            if (LastSortUpList[i].className.indexOf("headerSortUp") == -1) {
                let Text = LastSortUpList[i].innerText;
                Text = Text.substr(0, Text.length - 2);
                LastSortUpList[i].innerText = Text;
                LastSortUpList.splice(i, 1);
            }
        }

        let Temp = document.getElementsByClassName("headerSortDown");
        for (let i = 0; i < Temp.length; i++) {
            if (LastSortDownList.indexOf(Temp[i]) == -1) {
                Temp[i].innerText += " ↑";
                LastSortDownList.push(Temp[i]);
            }
        }
        Temp = document.getElementsByClassName("headerSortUp");
        for (let i = 0; i < Temp.length; i++) {
            if (LastSortUpList.indexOf(Temp[i]) == -1) {
                Temp[i].innerText += " ↓";
                LastSortUpList.push(Temp[i]);
            }
        }

        if (document.querySelector("#navbar > ul.nav.navbar-nav.navbar-right > li > ul > li:nth-child(3) > a > span").innerText != "个人中心") {
            document.querySelector("#navbar > ul.nav.navbar-nav.navbar-right > li > ul > li:nth-child(3) > a > span").innerText = "个人中心";
            document.querySelector("#navbar > ul.nav.navbar-nav.navbar-right > li > ul > li:nth-child(4)").style.display = "none";
            document.querySelector("#navbar > ul.nav.navbar-nav.navbar-right > li > ul > li:nth-child(5)").style.display = "none";
            document.querySelector("#navbar > ul.nav.navbar-nav.navbar-right > li > ul > li:nth-child(6)").style.display = "none";
            document.querySelector("#navbar > ul.nav.navbar-nav.navbar-right > li > ul").innerHTML = String(document.querySelector("#navbar > ul.nav.navbar-nav.navbar-right > li > ul").innerHTML).replaceAll("&nbsp;", "");
        }
    }, 100);

    Temp = document.getElementsByTagName("tr");
    for (let i = 0; i < Temp.length; i++) {
        Temp[i].setAttribute("align", "left");
    }
})();

function ShowMetal() {
    let Table = document.getElementById("rank").rows;
    let ParticipantsNumbers = Table.length - 1;
    for (let Rank = 1; Rank < Table.length; Rank++) {
        let MetalCell = Table[Rank].cells[0];
        MetalCell.innerHTML = (Rank == 1 ? "Winner" : Rank);
        if (Rank <= ParticipantsNumbers * 0.05 + 1) {
            MetalCell.className = "badge btn-warning";
        } else if (Rank <= ParticipantsNumbers * 0.20 + 1) {
            MetalCell.className = "badge";
        } else if (Rank <= ParticipantsNumbers * 0.45 + 1) {
            MetalCell.className = "badge btn-danger";
        } else {
            MetalCell.className = "badge badge-info";
        }
    }
}

function AddSubmission() {
    ProgressBar.setAttribute("value", AddedSubmissionCount);
    if (AddedSubmissionCount >= SubmitRecord.length) {
        return ShowMetal();
    }
    let Submission = SubmitRecord[AddedSubmissionCount];
    let Table = $("#rank");
    let Row = FindRow(Table, Submission.user_id);
    if (Row == null) {
        Table.append(CreateRowCode(Table, Submission));
    }
    Row = FindRow(Table, Submission.user_id);
    UpdateRow(Row, Submission);
    AddedSubmissionCount++;
    SortTable(Table[0].rows);
    ShowMetal();
    setTimeout(function() {
        AddSubmission()
    }, 10);
}

function SecondsToString(InputSeconds) {
    let Hours = Math.floor(InputSeconds / 3600);
    let Minutes = Math.floor((InputSeconds % 3600) / 60);
    let Seconds = InputSeconds % 60;
    return (Hours < 10 ? "0" : "") + Hours + ":" +
        (Minutes < 10 ? "0" : "") + Minutes + ":" +
        (Seconds < 10 ? "0" : "") + Seconds;
}

function StringToSeconds(InputString) {
    let SplittedString = InputString.split(":");
    return parseInt(SplittedString[0]) * 60 * 60 +
        parseInt(SplittedString[1]) * 60 +
        parseInt(SplittedString[2]);
}

function SetColor(Cell, IsAC, ErrorTimes) {
    ErrorTimes *= 10
    if (ErrorTimes > 255) {
        ErrorTimes = 255;
    }
    if (IsAC && ErrorTimes > 200) {
        ErrorTimes = 200;
    }
    let Temp = IsAC ? ErrorTimes : 255 - ErrorTimes;
    if (IsAC) {
        Cell.style = "background-color: rgb(" + Temp + ",255," + Temp + ");";
    } else {
        Cell.style = "background-color: rgb(255," + Temp + "," + Temp + ");";
    }
}

function UpdateRow(Row, Submission) {
    let Colum = parseInt(Submission.num) + 5;
    if (Colum > Row.cells.length - 1) {
        return;
    }
    let OldValue = Row.cells[Colum].innerHTML;
    if (!(OldValue.charAt(0) == "-" || OldValue == "")) {
        return;
    }
    let ErrorTimes = 0;
    if (OldValue != "") {
        ErrorTimes = parseInt(OldValue);
    }
    ErrorTimes = -ErrorTimes;
    if (parseInt(Submission.result) == 4) {
        Row.cells[4].innerHTML = SecondsToString(
            StringToSeconds(Row.cells[4].innerHTML) +
            parseInt(Submission.in_date) + ErrorTimes * 5 * 60);
        Row.cells[Colum].innerHTML = SecondsToString(parseInt(Submission.in_date));
        if (ErrorTimes != 0) {
            Row.cells[Colum].innerHTML += "(-" + ErrorTimes + ")";
        }
        SetColor(Row.cells[Colum], true, ErrorTimes);
        Row.cells[3].innerHTML = parseInt(Row.cells[3].innerHTML) + 1;
    } else {
        ErrorTimes++;
        Row.cells[Colum].innerHTML = "-" + ErrorTimes;
        SetColor(Row.cells[Colum], false, ErrorTimes);
    }
}

function SortTable(rows) {
    for (let i = 1; i < rows.length; i++) {
        if (rows[i].childNodes[1].innerText == document.getElementById("profile").innerText) {
            rows[i].style = "background-color: yellow;";
        }
        for (let j = 1; j < i; j++) {
            if (FirstBiggerThanSecond(rows[i], rows[j])) {
                SwapNode(rows[i], rows[j]);
            }
        }
    }
}

function SwapNode(Node1, Node2) {
    let Parent = Node1.parentNode;
    let Node1NextSibling = Node1.nextSibling;
    let Node2NextSibling = Node2.nextSibling;
    if (Node1NextSibling) Parent.insertBefore(Node2, Node1NextSibling);
    else Parent.appendChild(Node2);
    if (Node2NextSibling) Parent.insertBefore(Node1, Node2NextSibling);
    else Parent.appendChild(Node1);
}

function FirstBiggerThanSecond(Node1, Node2) {
    let Node1AC = parseInt(Node1.cells[3].innerHTML);
    let Node2AC = parseInt(Node2.cells[3].innerHTML);
    if (Node1AC != Node2AC) {
        return Node1AC > Node2AC;
    }
    return StringToSeconds(Node1.cells[4].innerHTML) < StringToSeconds(Node2.cells[4].innerHTML);
}

function CreateRowCode(Table, Submission) {
    let IsAC = (Submission.result == 4);
    let Output = "<tr>";
    Output += "<td></td>";
    Output += "<td><a href=\"userinfo.php?user=" + Submission.user_id + "\">" + Submission.user_id + "</a></td>";
    Output += "<td>" + (Submission.nick.length > 10 ? String(Submission.nick).substring(0, 10) + "..." : Submission.nick) + "</td>";
    Output += "<td>" + (IsAC ? "1" : "0") + "</td>";
    Output += "<td>" + SecondsToString(IsAC ? Submission.in_date : 0) + "</td>";
    let ProblemCount = Table[0].rows[0].cells.length - 5;
    for (let i = 0; i < ProblemCount; i++) {
        if (i == Submission.num) {
            Output += "<td class=\"well " + (IsAC ? "green" : "red") + "\">" +
                (IsAC ? SecondsToString(Submission.in_date) : -1) +
                "</td>";
        } else {
            Output += "<td class=\"well\" style=\"background-color:#eeeeee\"></td>";
        }
    }
    Output += "</tr>";
    return Output;
}

function FindRow(Table, UID) {
    Table = Table[0].rows;
    for (let i = 0; i < Table.length; i++) {
        if (Table[i].cells[1].innerText == UID) {
            return Table[i];
        }
    }
    return null;
}

function PlaySubmission() {
    document.querySelector("#rank > tbody").innerHTML = "";
    let Data = "";
    Data += "<tr class=\"toprow\">";
    Data += "<th width=\"10%\" class=\"header\">排名</th>";
    Data += "<th width=\"10%\" class=\"header\">用户</th>";
    Data += "<th width=\"15%\" class=\"header\">昵称</th>";
    Data += "<th width=\"5%\" class=\"header\">AC数</th>";
    Data += "<th width=\"10%\" class=\"header\">罚时</th>";
    for (let i = 0; i < QuestionSize; i++) {
        Data += "<th width=\"" + (50 / QuestionSize) + "%\" class=\"header\">" +
            "<a href=\"problem.php?" + location.href.substr(location.href.indexOf("cid=")) + "&pid=" + i + "\">" + String.fromCharCode(65 + i) + "</a>" +
            "</th>";
    }
    Data += "</tr>";
    document.querySelector("#rank > thead").innerHTML = Data;
    ProgressBar.setAttribute("max", SubmitRecord.length);
    AddedSubmissionCount = 0;
    AddSubmission();
}

function ReloadRank() {
    document.getElementsByTagName("progress")[0].removeAttribute("max");
    document.getElementsByTagName("progress")[0].removeAttribute("value");
    let Request = new XMLHttpRequest();
    Request.onreadystatechange = function() {
        if (Request.readyState == 4 && Request.status == 200) {
            var ResponseText = Request.responseText;
            var StartPosition = ResponseText.indexOf("var solutions=");
            StartPosition += 14;
            var EndPosition = ResponseText.indexOf(";", StartPosition);
            SubmitRecord = JSON.parse(ResponseText.substring(StartPosition, EndPosition));
            PlaySubmission();
        }
    };
    let NewURL = new URL(location.href);
    NewURL.pathname = "/contestrank2.php";
    Request.open("GET", NewURL.toString(), true);
    Request.send();
}
