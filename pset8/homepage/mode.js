
document.addEventListener("DOMContentLoaded", function(){
    let status = document.querySelector(".inner-switch");
    let off = true;
    status.addEventListener('click', function(){
        if(off == true){
            off = false;
            document.body.style.backgroundColor="black";
            document.body.style.color= "white";
            status.innerHTML = "ON";

        }else{
            document.body.style.backgroundColor="white";
            document.body.style.color= "black";
            status.innerHTML = "OFF";
            off = true;
        }

    });
 });
