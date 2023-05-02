// ==UserScript==
// @name         XMOJ
// @version      0.1
// @description  Test
// @author       @langningchen
// @match        http://www.xmoj.tech/*
// @icon         https://www.google.com/s2/favicons?sz=64&domain=xmoj.tech
// @require      https://cdn.bootcdn.net/ajax/libs/jszip/3.10.1/jszip.min.js
// @require      https://cdn.bootcdn.net/ajax/libs/crypto-js/4.1.1/crypto-js.min.js
// @require      https://cdn.bootcdn.net/ajax/libs/crypto-js/4.1.1/hmac-sha1.min.js
// @require      https://raw.githubusercontent.com/drudru/ansi_up/master/ansi_up.js
// @grant        GM_registerMenuCommand
// ==/UserScript==

let QuestionSize = 0;
let AddedSubmissionCount = 0;
let ProgressBar = null;
let SubmitRecord = null;
(async () => {
    "use strict";
    GM_registerMenuCommand("重置数据", () => {
        for (let i = 0; i < localStorage.length; i++) {
            if (localStorage.key(i).substr(0, 10) == "UserScript") {
                localStorage.removeItem(localStorage.key(i));
            }
        }
        location.reload();
    });

    if (document.querySelector("#profile") != null &&
        document.querySelector("#profile").innerHTML == "登录" &&
        location.pathname != "/login.php" &&
        location.pathname != "/loginpage.php" &&
        location.pathname != "/lostpassword.php") {
        localStorage.setItem("UserScript-LastPage", location.pathname + location.search);
        location.href = "loginpage.php";
    }


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

    let Style = document.createElement("style");
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

    if (location.pathname == "/problemset.php") {
        document.querySelector("body > div > div > center > table:nth-child(2) > tbody > tr > td:nth-child(2) > form > input").placeholder = "题目编号";
        document.querySelector("body > div > div > center > table:nth-child(2) > tbody > tr > td:nth-child(2) > form > button").innerText = "确认";
        document.querySelector("body > div > div > center > table:nth-child(2) > tbody > tr > td:nth-child(3) > form > input").placeholder = "标题或内容";
        document.querySelector("#problemset > thead > tr > th:nth-child(1)").innerText = "状态";
    } else if (location.pathname == "/problem.php") {
        document.getElementsByTagName("center")[1].style.display = "none";
        $(".copy-btn").click(() => {
            const span = $(this).next().find(".sampledata");
            if (!span.length) {
                $(this).text("未找到pre").addClass("done");
                setTimeout(() => {
                    $(".copy-btn").text("复制").removeClass("done");
                }, 1000);
                return;
            }
            const textarea = $("<textarea></textarea>").attr("readonly", "readonly").text(span.text());
            document.body.appendChild(textarea[0]);
            textarea.select();
            if (document.execCommand("copy")) {
                $(this).text("复制成功").addClass("done");
                setTimeout(() => {
                    $(".copy-btn").text("复制").removeClass("done");
                }, 1000);
            }
            document.body.removeChild(textarea[0]);
        });
        let IOFileElement = document.querySelector("body > div > div > center > h3");
        if (IOFileElement != null) {
            while (IOFileElement.childNodes.length >= 1) {
                IOFileElement.parentNode.insertBefore(IOFileElement.childNodes[0], IOFileElement);
            }
            IOFileElement.parentNode.insertBefore(document.createElement("br"), IOFileElement);
            IOFileElement.remove();
            let IOFileName = document.querySelector("body > div > div > center").childNodes[2].data.trim();
            IOFileName = IOFileName.substr(0, IOFileName.length - 3);
            let SearchParams = new URLSearchParams(location.search);
            if (SearchParams.get("id") != null) {
                localStorage.setItem("UserScript-Problem-" + SearchParams.get("id") + "-IOFileName", IOFileName);
            } else if (SearchParams.get("cid") != null && SearchParams.get("pid") != null) {
                localStorage.setItem("UserScript-Contest-" + SearchParams.get("cid") + "-Problem-" + SearchParams.get("pid") + "-IOFileName", IOFileName);
            }
        }
    } else if (location.pathname == "/status.php") {
        const SizeToStringSize = (Memory) => {
            if (Memory < 1024) {
                return Memory + "B";
            } else if (Memory < 1024 * 1024) {
                return (Memory / 1024).toFixed(2) + "KB";
            } else if (Memory < 1024 * 1024 * 1024) {
                return (Memory / 1024 / 1024).toFixed(2) + "MB";
            } else {
                return (Memory / 1024 / 1024 / 1024).toFixed(2) + "GB";
            }
        };
        const TimeToStringTime = (Time) => {
            if (Time < 1000) {
                return Time + "ms";
            } else if (Time < 1000 * 60) {
                return (Time / 1000).toFixed(2) + "s";
            } else if (Time < 1000 * 60 * 60) {
                return (Time / 1000 / 60).toFixed(2) + "min";
            } else {
                return (Time / 1000 / 60 / 60).toFixed(2) + "h";
            }
        };
        document.querySelector("#simform > input:nth-child(2)").style.display = "none";
        document.querySelector("#simform").innerHTML = document.querySelector("#simform").innerHTML.replaceAll("用户:", "");
        document.querySelector("#simform").innerHTML = document.querySelector("#simform").innerHTML.replaceAll(":", ": ");
        document.querySelector("#simform").style.paddingBottom = "7px";
        let CompareButton = document.createElement("button");
        document.querySelector("body > div.container > div > div.input-append").appendChild(CompareButton);
        CompareButton.className = "UserScriptDefinedButton";
        CompareButton.innerText = "比较提交记录";
        CompareButton.onclick = () => {
            location.href = "comparesource.php";
        };
        CompareButton.style.marginBottom = "7px";

        document.querySelector("#result-tab > thead > tr > th:nth-child(1)").style.display = "none";
        document.querySelector("#result-tab > thead > tr > th:nth-child(3)").style.display = "none";
        document.querySelector("#result-tab > thead > tr > th:nth-child(11)").style.display = "none";
        document.querySelector("#result-tab > thead > tr > th:nth-child(12)").style.display = "none";
        let Temp = document.querySelector("#result-tab > tbody").childNodes;
        for (let i = 1; i < Temp.length; i += 2) {
            Temp[i].childNodes[0].style.display = "none";
            Temp[i].childNodes[1].innerHTML = "<a href=\"showsource.php?id=" + Temp[i].childNodes[1].innerText + "\">" + Temp[i].childNodes[1].innerText + "</a>";
            Temp[i].childNodes[2].style.display = "none";
            Temp[i].childNodes[7].innerText = Temp[i].childNodes[7].childNodes[0].innerText;
            Temp[i].childNodes[5].childNodes[0].innerText = SizeToStringSize(Temp[i].childNodes[5].childNodes[0].innerText);
            Temp[i].childNodes[6].childNodes[0].innerText = TimeToStringTime(Temp[i].childNodes[6].childNodes[0].innerText);
            Temp[i].childNodes[8].innerText = SizeToStringSize(Temp[i].childNodes[8].innerText.substr(0, Temp[i].childNodes[8].innerText.length - 1));
            Temp[i].childNodes[10].style.display = "none";
            Temp[i].childNodes[11].style.display = "none";
        }

        document.querySelector("#result-tab > tbody").innerHTML =
            String(document.querySelector("#result-tab > tbody").innerHTML).replaceAll("class=\"center\"", "");

        let Rows = document.getElementById("result-tab").rows;
        let Points = Array();
        for (let i = Rows.length - 1; i > 0; i--) {
            Rows[i].cells[4].className = "td_result";
            let SolutionID = Rows[i].cells[1].innerText;
            if (Rows[i].cells[4].children.length == 2) {
                Points[SolutionID] = Rows[i].cells[4].children[1].innerText;
                Rows[i].cells[4].children[1].remove();
            }
            Rows[i].cells[4].innerHTML += "<img height=\"18\" width=\"18\" src=\"image/loader.gif\">";
            setTimeout(() => {
                RefreshResult(SolutionID);
            }, 0);
        }

        const FindRow = (SolutionID) => {
            let Rows = document.getElementById("result-tab").rows;
            for (let i = 1; i < Rows.length; i++) {
                if (Rows[i].cells[1].innerText == SolutionID) {
                    return Rows[i];
                }
            }
            return null;
        }

        const RefreshResult = async (SolutionID) => {
            let CurrentRow = FindRow(SolutionID);
            await fetch("status-ajax.php?solution_id=" + SolutionID)
                .then((Response) => { return Response.text(); })
                .then((Response) => {
                    let ResponseData = Response.split(",");
                    CurrentRow.cells[5].innerHTML = "<div id=\"center\" class=\"red\">" + SizeToStringSize(ResponseData[1]) + "</div>";
                    CurrentRow.cells[6].innerHTML = "<div id=\"center\" class=\"red\">" + TimeToStringTime(ResponseData[2]) + "</div>";
                    let TempHTML = "<span class=\"" + judge_color[ResponseData[0]] + "\">";
                    if (ResponseData[0] == 6 || ResponseData[0] == 10 || ResponseData[0] == 11) {
                        TempHTML += "<a style=\"color: white\" href=\"" + (ResponseData[0] == 11 ? "ce" : "re") + "info.php?sid=" + SolutionID + "\">" + judge_result[ResponseData[0]] + "</a>";
                    } else {
                        TempHTML += judge_result[ResponseData[0]];
                    }
                    TempHTML += "</span>";
                    if (Points[SolutionID] != undefined) {
                        TempHTML += "<span class=\"btn btn-info\">" + Points[SolutionID] + "</span>";
                    }
                    if (ResponseData[0] < 4) {
                        setTimeout(() => {
                            RefreshResult(SolutionID)
                        }, 500);
                        TempHTML += "<img height=\"18\" width=\"18\" src=\"image/loader.gif\">";
                    }
                    CurrentRow.cells[4].innerHTML = TempHTML;
                });
        };
    } else if (location.pathname == "/contest.php") {
        onfocus = () => {
            location.reload();
        };
        clock = () => {
            setInterval(() => {
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
            }, 200);
        }
        if (location.href.indexOf("?cid=") == -1) {
            document.querySelector("body > div > div > center").innerHTML =
                String(document.querySelector("body > div > div > center").innerHTML).replaceAll("ServerTime:", "服务器时间：");
            document.querySelector("body > div > div > center > table").style.marginTop = "10px";
            document.querySelector("body > div > div > center > form").childNodes[0].data = "";
            document.querySelector("body > div > div > center > form > input[type=text]:nth-child(1)").className = "form-control";
            document.querySelector("body > div > div > center > form > input[type=text]:nth-child(1)").style.width = "200px";
            document.querySelector("body > div > div > center > form > input[type=text]:nth-child(1)").style.display = "inline-block";
            document.querySelector("body > div > div > center > form > input[type=submit]:nth-child(2)").value = "搜索";
            document.querySelector("body > div > div > center > form > input[type=submit]:nth-child(2)").className = "form-control";
            document.querySelector("body > div > div > center > form > input[type=submit]:nth-child(2)").style.width = "unset";
            document.querySelector("body > div > div > center > form > input[type=submit]:nth-child(2)").style.display = "inline-block";
            document.querySelector("body > div > div > center > table > thead > tr").childNodes[0].innerText = "编号";
            document.querySelector("body > div > div > center > table > thead > tr").childNodes[1].innerText = "标题";
            document.querySelector("body > div > div > center > table > thead > tr").childNodes[2].innerText = "状态";
            document.querySelector("body > div > div > center > table > thead > tr").childNodes[3].style.display = "none";
            document.querySelector("body > div > div > center > table > thead > tr").childNodes[4].innerText = "创建者";
            let Temp = document.querySelector("body > div > div > center > table > tbody").childNodes;
            for (let i = 1; i < Temp.length; i++) {
                let CurrentElement = Temp[i].childNodes[2].childNodes;
                if (CurrentElement[1].childNodes[0].data.indexOf("运行中") != -1) {
                    let Time = String(CurrentElement[1].childNodes[1].innerText).substr(4);
                    let Day = parseInt(Time.substring(0, Time.indexOf("天")));
                    let Hour = parseInt(Time.substring(Time.indexOf("天") + 1, Time.indexOf("小时")));
                    let Minute = parseInt(Time.substring(Time.indexOf("小时") + 2, Time.indexOf("分")));
                    let Second = parseInt(Time.substring(Time.indexOf("分") + 1, Time.indexOf("秒")));
                    let TimeStamp = new Date().getTime() + diff + ((((isNaN(Day) ? 0 : Day) * 24 + Hour) * 60 + Minute) * 60 + Second) * 1000;
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
                Temp[i].childNodes[3].style.display = "none";
                Temp[i].childNodes[4].innerHTML = "<a href=\"userinfo.php?user=" + Temp[i].childNodes[4].innerHTML + "\">" + Temp[i].childNodes[4].innerHTML + "</a>";
            }

            setInterval(() => {
                Temp = document.getElementsByClassName("UpdateByJS");
                for (let i = 0; i < Temp.length; i++) {
                    let TimeStamp = parseInt(Temp[i].getAttribute("EndTime"));
                    TimeStamp = TimeStamp - new Date().getTime() - diff;
                    if (TimeStamp < 0) {
                        location.reload();
                    }
                    let CurrentDate = new Date(TimeStamp);
                    let Day = parseInt(TimeStamp / 1000 / 60 / 60 / 24);
                    let Hour = CurrentDate.getUTCHours();
                    let Minute = CurrentDate.getUTCMinutes();
                    let Second = CurrentDate.getUTCSeconds();
                    Temp[i].innerText = (Day != 0 ? Day + "天" : "") +
                        (Hour < 10 ? "0" : "") + Hour + "小时" +
                        (Minute < 10 ? "0" : "") + Minute + "分" +
                        (Second < 10 ? "0" : "") + Second + "秒";
                }
            }, 200);
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
            StaticButton.onclick = () => {
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

            document.querySelector("#problemset").style.marginTop = "10px";
            let OpenAllDiv = document.createElement("div");
            OpenAllDiv.style.marginTop = "20px";
            OpenAllDiv.style.textAlign = "left";
            document.querySelector("body > div > div > center").insertBefore(OpenAllDiv, document.querySelector("#problemset"));
            let OpenAllButton = document.createElement("button");
            OpenAllButton.classList.add("UserScriptDefinedButton");
            OpenAllButton.innerText = "打开全部题目";
            OpenAllDiv.appendChild(OpenAllButton);
            OpenAllButton.onclick = () => {
                let Rows = document.querySelector("#problemset > tbody").rows;
                for (let i = 0; i < Rows.length; i++) {
                    window.open(Rows[i].children[2].children[0].href, "_blank");
                }
            }
            let OpenUnsolvedButton = document.createElement("button");
            OpenUnsolvedButton.classList.add("UserScriptDefinedButton");
            OpenUnsolvedButton.innerText = "打开未解决题目";
            OpenAllDiv.appendChild(OpenUnsolvedButton);
            OpenUnsolvedButton.onclick = () => {
                let Rows = document.querySelector("#problemset > tbody").rows;
                for (let i = 0; i < Rows.length; i++) {
                    if (Rows[i].children[0].childElementCount == 0 ||
                        Rows[i].children[0].children[0].classList.contains("status_n")) {
                        window.open(Rows[i].children[2].children[0].href, "_blank");
                    }
                }
            }
            let OpenSolvedButton = document.createElement("button");
            OpenSolvedButton.classList.add("UserScriptDefinedButton");
            OpenSolvedButton.innerText = "打开已解决题目";
            OpenAllDiv.appendChild(OpenSolvedButton);
            OpenSolvedButton.onclick = () => {
                let Rows = document.querySelector("#problemset > tbody").rows;
                for (let i = 0; i < Rows.length; i++) {
                    if (Rows[i].children[0].childElementCount != 0 &&
                        Rows[i].children[0].children[0].classList.contains("status_y")) {
                        window.open(Rows[i].children[2].children[0].href, "_blank");
                    }
                }
            }
            let OpenUnattemptedButton = document.createElement("button");
            OpenUnattemptedButton.classList.add("UserScriptDefinedButton");
            OpenUnattemptedButton.innerText = "打开未尝试题目";
            OpenAllDiv.appendChild(OpenUnattemptedButton);
            OpenUnattemptedButton.onclick = () => {
                let Rows = document.querySelector("#problemset > tbody").rows;
                for (let i = 0; i < Rows.length; i++) {
                    if (Rows[i].children[0].childElementCount == 0) {
                        window.open(Rows[i].children[2].children[0].href, "_blank");
                    }
                }
            }
            let OpenUnsolvedAttemptedButton = document.createElement("button");
            OpenUnsolvedAttemptedButton.classList.add("UserScriptDefinedButton");
            OpenUnsolvedAttemptedButton.innerText = "打开已尝试未解决题目";
            OpenAllDiv.appendChild(OpenUnsolvedAttemptedButton);
            OpenUnsolvedAttemptedButton.onclick = () => {
                let Rows = document.querySelector("#problemset > tbody").rows;
                for (let i = 0; i < Rows.length; i++) {
                    if (Rows[i].children[0].childElementCount != 0 &&
                        !Rows[i].children[0].children[0].classList.contains("status_y")) {
                        window.open(Rows[i].children[2].children[0].href, "_blank");
                    }
                }
            }
        }
    } else if (location.pathname == "/contestrank-oi.php") {
        onfocus = () => {
            location.reload();
        };
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
            DownloadButton.onclick = () => {
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
            let ReloadProgress = document.createElement("button");
            ReloadProgress.classList.add("UserScriptDefinedButton");
            ReloadProgress.style.marginRight = "20px";
            ReloadProgress.style.marginBottom = "5px";
            ReloadProgress.innerText = "重新播放动画";
            ReloadProgress.onclick = () => {
                PlaySubmission();
            }
            document.querySelector("body > div.container > div").insertBefore(ReloadProgress, document.querySelector("#rank"));
            let Reload = document.createElement("button");
            Reload.classList.add("UserScriptDefinedButton");
            Reload.innerText = "重新加载排名";
            Reload.onclick = () => {
                ReloadRank();
            }
            document.querySelector("body > div.container > div").insertBefore(Reload, document.querySelector("#rank"));
        }
    } else if (location.pathname == "/contestrank-correct.php") {
        document.querySelector("body > div.container > div > center > a").style.display = "none";
    } else if (location.pathname == "/submitpage.php") {
        document.querySelector("#enable_O2").checked = true;
        document.querySelector("#frmSolution").childNodes[0].nodeValue = "题目";
        document.querySelector("#language_span").childNodes[0].nodeValue = "语言：";
        document.querySelector("#language").style.marginTop = "10px";
        document.querySelector("#language").style.marginBottom = "10px";
        document.querySelector("#source").classList.add("form-control");
        let CheckInterval = setInterval(() => {
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
        let ErrorElement = document.createElement("div");
        ErrorElement.style.marginTop = "10px";
        ErrorElement.style.display = "none";
        ErrorElement.style.textAlign = "left";
        ErrorElement.style.padding = "10px";
        document.querySelector("body > div > div > center").appendChild(ErrorElement);
        let ErrorMessage = document.createElement("div");
        ErrorMessage.style.whiteSpace = "pre";
        ErrorMessage.style.backgroundColor = "rgb(0, 0, 0, 0.1)";
        ErrorMessage.style.padding = "10px";
        ErrorMessage.style.borderRadius = "5px";
        ErrorElement.appendChild(ErrorMessage);
        let PassCheck = document.createElement("button");
        PassCheck.classList.add("UserScriptDefinedButton");
        PassCheck.style.marginTop = "10px";
        PassCheck.innerText = "我没错！让我提交！";
        PassCheck.onclick = () => {
            document.querySelector("#Submit").disabled = true;
            document.querySelector("#Submit").value = "正在提交...";
            document.querySelector("#frmSolution").submit();
        }
        ErrorElement.appendChild(PassCheck);

        document.querySelector("#Submit").type = "button";
        document.querySelector("#Submit").onclick = async () => {
            ErrorElement.style.display = "none";
            document.querySelector("#Submit").disabled = true;
            document.querySelector("#Submit").value = "正在检查...";
            eAL.toggle("source");
            eAL.toggle("source");
            let Source = document.getElementById("source").value;
            let SearchParams = new URL(location.href).searchParams;
            if (SearchParams.get("id") != null) {
                let IOFileName = localStorage.getItem("UserScript-Problem-" + SearchParams.get("id") + "-IOFileName");
                if (IOFileName != null) {
                    if (Source.indexOf(IOFileName) == -1) {
                        ErrorElement.style.display = "block";
                        ErrorMessage.style.color = "red";
                        ErrorMessage.innerText = "此题输入输出文件名为" + IOFileName + "，请检查是否填错";
                        document.querySelector("#Submit").disabled = false;
                        document.querySelector("#Submit").value = "提交";
                        return false;
                    }
                }
            } else if (SearchParams.get("cid") != null && SearchParams.get("pid") != null) {
                let IOFileName = localStorage.getItem("UserScript-Contest-" + SearchParams.get("cid") + "-Problem-" + SearchParams.get("pid") + "-IOFileName");
                if (IOFileName != null) {
                    if (Source.indexOf(IOFileName) == -1) {
                        ErrorElement.style.display = "block";
                        ErrorMessage.style.color = "red";
                        ErrorMessage.innerText = "此题输入输出文件名为" + IOFileName + "，请检查是否填错";
                        document.querySelector("#Submit").disabled = false;
                        document.querySelector("#Submit").value = "提交";
                        return false;
                    }
                }
            } else if (Source == "") {
                ErrorElement.style.display = "block";
                ErrorMessage.style.color = "red";
                ErrorMessage.innerText = "源代码为空";
                document.querySelector("#Submit").disabled = false;
                document.querySelector("#Submit").value = "提交";
                return false;
            } else if (Source.indexOf("int main") == -1) {
                ErrorElement.style.display = "block";
                ErrorMessage.style.color = "red";
                ErrorMessage.innerText = "主函数返回值类型错误";
                document.querySelector("#Submit").disabled = false;
                document.querySelector("#Submit").value = "提交";
                return false;
            }
            await fetch("https://gcc.godbolt.org/api/compiler/g131/compile", {
                "headers": {
                    "accept": "application/json"
                },
                "body": Source,
                "method": "POST"
            })
                .then(Response => Response.json())
                .then(Response => {
                    var Transferer = new AnsiUp();
                    let CompileError = "";
                    for (let i = 0; i < Response.stderr.length; i++) {
                        CompileError += Transferer.ansi_to_html(Response.stderr[i].text) + "<br>";
                    }
                    if (CompileError != "") {
                        ErrorElement.style.display = "block";
                        ErrorMessage.style.color = "";
                        ErrorMessage.innerHTML = "编译错误：<br>" + CompileError;
                        document.querySelector("#Submit").disabled = false;
                        document.querySelector("#Submit").value = "提交";
                        return false;
                    }
                });
            if (ErrorElement.style.display == "none") {
                PassCheck.click();
            }
            return true;
        };
    } else if (location.pathname == "/modifypage.php") {
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
        ExportACCode.onclick = () => {
            let ExportProgressBar = document.getElementsByTagName("progress")[0] || document.createElement("progress");
            ExportProgressBar.removeAttribute("value");
            ExportProgressBar.removeAttribute("max");
            document.querySelector("body > div.container > div").appendChild(ExportProgressBar);
            ExportACCode.innerText = "正在导出...";
            let Request = new XMLHttpRequest();
            Request.onreadystatechange = () => {
                if (Request.readyState == 4) {
                    if (Request.status == 200) {
                        let Response = Request.responseText;
                        let ACCode = Response.split("------------------------------------------------------\r\n");
                        let Zip = new JSZip();
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
                            .then(Content => {
                                let CurrentBlob = new Blob([Content], { type: "application/zip" });
                                let CurrentURL = URL.createObjectURL(CurrentBlob);
                                let CurrentLink = document.createElement("a");
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
    } else if (location.pathname == "/userinfo.php") {
        let Temp = document.getElementById("submission").childNodes;
        for (let i = 0; i < Temp.length; i++) {
            Temp[i].remove();
        }
        eval(document.querySelector("body > script:nth-child(6)").innerHTML);
    } else if (location.pathname == "/conteststatistics.php") {
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
            let CurrentRow = Temp[i].children;
            for (let j = 0; j < CurrentRow.length; j++) {
                if (j == 9 || j == 14) {
                    CurrentRow[j].style.display = "none";
                }
                if (CurrentRow[j].innerText == "") {
                    CurrentRow[j].innerText = "0";
                }
            }
        }
    } else if (location.pathname == "/comparesource.php") {
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
        CompareButton.onclick = () => {
            location.href = "/comparesource.php?left=" + LeftCode.value + "&right=" + RightCode.value;
        };
    } else if (location.pathname == "/loginpage.php") {
        let ErrorText = document.createElement("div");
        ErrorText.style.color = "red";
        ErrorText.style.marginBottom = "5px";
        document.querySelector("#login").appendChild(ErrorText);
        let LoginButton = document.querySelector("#login > div:nth-child(4) > div.col-sm-offset-4.col-sm-4 > button");
        LoginButton.type = "button";
        LoginButton.onclick = async () => {
            let Username = document.querySelector("#login > div:nth-child(2) > div > input").value;
            let Password = document.querySelector("#login > div:nth-child(3) > div > input").value;
            if (Username == "" ||
                Password == "") {
                ErrorText.innerText = "用户名或密码不能为空";
            } else {
                await fetch("http://www.xmoj.tech/login.php", {
                    method: "POST",
                    headers: {
                        "Content-Type": "application/x-www-form-urlencoded"
                    },
                    body: "user_id=" + encodeURIComponent(Username) +
                        "&password=" + hex_md5(Password)
                })
                    .then(Response => { return Response.text(); })
                    .then(Response => {
                        console.log(Response);
                        if (Response.indexOf("history.go(-2);") != -1) {
                            localStorage.setItem("UserScript-Username", Username);
                            localStorage.setItem("UserScript-Password", Password);
                            let NewPage = localStorage.getItem("UserScript-LastPage");
                            if (NewPage == null) {
                                NewPage = "/index.php";
                            }
                            location.href = NewPage;
                        } else {
                            localStorage.removeItem("UserScript-Username");
                            localStorage.removeItem("UserScript-Password");
                            Response = Response.substr(Response.indexOf("alert('") + 7);
                            Response = Response.substr(0, Response.indexOf("');"));
                            if (Response == "UserName or Password Wrong!") {
                                ErrorText.innerText = "用户名或密码错误！";
                            }
                            else {
                                ErrorText.innerText = Response;
                            }
                        }
                    });
            }
        };
        if (localStorage.getItem("UserScript-Username") != null &&
            localStorage.getItem("UserScript-Password") != null) {
            document.querySelector("#login > div:nth-child(2) > div > input").value = localStorage.getItem("UserScript-Username");
            document.querySelector("#login > div:nth-child(3) > div > input").value = localStorage.getItem("UserScript-Password");
            LoginButton.click();
        }
    } else if (location.pathname == "/contest_video.php") {
        let ScriptData = document.querySelector("body > div > div > center > script").innerHTML;
        eval(ScriptData);
        ScriptData = ScriptData.substr(ScriptData.indexOf("{"));
        ScriptData = ScriptData.substr(0, ScriptData.indexOf("}") + 1);
        ScriptData = ScriptData.replace(/([a-zA-Z0-9]+) ?:/g, "\"$1\":");
        ScriptData = ScriptData.replace(/'/g, "\"");
        let VideoData = JSON.parse(ScriptData);
        const RandomUUID = () => {
            const t = "0123456789abcdef";
            let e = [];
            for (let r = 0; r < 36; r++)
                e[r] = t.substr(Math.floor(16 * Math.random()), 1);
            e[14] = "4";
            e[19] = t.substr(3 & e[19] | 8, 1);
            e[8] = e[13] = e[18] = e[23] = "-";
            return e.join("");
        };
        let URLParams = new URLSearchParams({
            "AccessKeyId": VideoData.accessKeyId,
            "Action": "GetPlayInfo",
            "VideoId": VideoData.vid,
            "Formats": "",
            "AuthTimeout": 7200,
            "Rand": RandomUUID(),
            "SecurityToken": VideoData.securityToken,
            "StreamType": "video",
            "Format": "JSON",
            "Version": "2017-03-21",
            "SignatureMethod": "HMAC-SHA1",
            "SignatureVersion": "1.0",
            "SignatureNonce": RandomUUID(),
            "PlayerVersion": "2.9.3",
            "Channel": "HTML5"
        });
        URLParams.sort();
        await fetch("https://vod." + VideoData.region + ".aliyuncs.com/?" +
            URLParams.toString() +
            "&Signature=" +
            encodeURIComponent(CryptoJS.HmacSHA1("GET&%2F&" + encodeURIComponent(URLParams.toString()),
                VideoData.accessKeySecret + "&").toString(CryptoJS.enc.Base64)))
            .then(Response => { return Response.json(); })
            .then(Response => {
                console.log(Response["VideoBase"]["Title"]);
                console.log(Response["PlayInfoList"]["PlayInfo"][0]["PlayURL"]);
                let DownloadButton = document.createElement("a");
                DownloadButton.classList.add("UserScriptDefinedButton");
                DownloadButton.innerText = "下载";
                DownloadButton.href = Response["PlayInfoList"]["PlayInfo"][0]["PlayURL"];
                DownloadButton.download = Response["VideoBase"]["Title"];
                document.querySelector("body > div > div > center").appendChild(DownloadButton);
            });
    } else if (location.pathname == "/login.php") {
        location.href = "/loginpage.php";
    }


    let Temp = document.getElementsByClassName("status_y");
    for (let i = 0; i < Temp.length; i++) {
        Temp[i].innerText = "✓";
    }
    Temp = document.getElementsByClassName("status_n");
    for (let i = 0; i < Temp.length; i++) {
        Temp[i].innerText = "×";
    }

    let LastSortDownList = [];
    let LastSortUpList = [];
    setInterval(() => {
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

        if (document.querySelector("#profile").innerHTML == "登录") {
            if (document.querySelector("#navbar > ul.nav.navbar-nav.navbar-right > li > ul").childNodes.length == 3) {
                document.querySelector("#navbar > ul.nav.navbar-nav.navbar-right > li > ul").childNodes[3].remove();
            }
        }
        else {
            if (document.querySelector("#navbar > ul.nav.navbar-nav.navbar-right > li > ul > li:nth-child(3) > a > span").innerText != "个人中心") {
            document.querySelector("#navbar > ul.nav.navbar-nav.navbar-right > li > ul > li:nth-child(3) > a > span").innerText = "个人中心";
            document.querySelector("#navbar > ul.nav.navbar-nav.navbar-right > li > ul > li:nth-child(4)").style.display = "none";
            document.querySelector("#navbar > ul.nav.navbar-nav.navbar-right > li > ul > li:nth-child(5)").style.display = "none";
            document.querySelector("#navbar > ul.nav.navbar-nav.navbar-right > li > ul > li:nth-child(6)").style.display = "none";
            document.querySelector("#navbar > ul.nav.navbar-nav.navbar-right > li > ul").innerHTML = String(document.querySelector("#navbar > ul.nav.navbar-nav.navbar-right > li > ul").innerHTML).replaceAll("&nbsp;", "");
        }
        }
    }, 100);

    Temp = document.getElementsByTagName("tr");
    for (let i = 0; i < Temp.length; i++) {
        Temp[i].setAttribute("align", "left");
    }
})();

const ShowMetal = () => {
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

const AddSubmission = () => {
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
    setTimeout(() => {
        AddSubmission()
    }, 10);
}

const SecondsToString = (InputSeconds) => {
    let Hours = Math.floor(InputSeconds / 3600);
    let Minutes = Math.floor((InputSeconds % 3600) / 60);
    let Seconds = InputSeconds % 60;
    return (Hours < 10 ? "0" : "") + Hours + ":" +
        (Minutes < 10 ? "0" : "") + Minutes + ":" +
        (Seconds < 10 ? "0" : "") + Seconds;
}

const StringToSeconds = (InputString) => {
    let SplittedString = InputString.split(":");
    return parseInt(SplittedString[0]) * 60 * 60 +
        parseInt(SplittedString[1]) * 60 +
        parseInt(SplittedString[2]);
}

const SetColor = (Cell, IsAC, ErrorTimes) => {
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

const UpdateRow = (Row, Submission) => {
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

const SortTable = (rows) => {
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

const SwapNode = (Node1, Node2) => {
    let Parent = Node1.parentNode;
    let Node1NextSibling = Node1.nextSibling;
    let Node2NextSibling = Node2.nextSibling;
    if (Node1NextSibling) Parent.insertBefore(Node2, Node1NextSibling);
    else Parent.appendChild(Node2);
    if (Node2NextSibling) Parent.insertBefore(Node1, Node2NextSibling);
    else Parent.appendChild(Node1);
}

const FirstBiggerThanSecond = (Node1, Node2) => {
    let Node1AC = parseInt(Node1.cells[3].innerHTML);
    let Node2AC = parseInt(Node2.cells[3].innerHTML);
    if (Node1AC != Node2AC) {
        return Node1AC > Node2AC;
    }
    return StringToSeconds(Node1.cells[4].innerHTML) < StringToSeconds(Node2.cells[4].innerHTML);
}

const CreateRowCode = (Table, Submission) => {
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

const FindRow = (Table, UID) => {
    Table = Table[0].rows;
    for (let i = 0; i < Table.length; i++) {
        if (Table[i].cells[1].innerText == UID) {
            return Table[i];
        }
    }
    return null;
}

const PlaySubmission = () => {
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

const ReloadRank = async () => {
    document.getElementsByTagName("progress")[0].removeAttribute("max");
    document.getElementsByTagName("progress")[0].removeAttribute("value");
    let NewURL = new URL(location.href);
    NewURL.pathname = "/contestrank2.php";
    await fetch(NewURL.toString())
        .then(Response => Response.text())
        .then(Response => {
            let StartPosition = Response.indexOf("var solutions=");
            StartPosition += 14;
            let EndPosition = Response.indexOf(";", StartPosition);
            SubmitRecord = JSON.parse(Response.substring(StartPosition, EndPosition));
            PlaySubmission();
        });
}
