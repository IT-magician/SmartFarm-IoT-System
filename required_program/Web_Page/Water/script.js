function setWaterDisplay(percent){
  document.getElementById("count").innerHTML = percent;
  document.getElementById("water").style.transform='translate(0'+','+(100-document.getElementById("count").innerHTML)+'%)';
}
function setWaterDisplayFullOrEmpty(isTrue)
{
  if(isTrue)
    setWaterDisplay(90);
  else
    setWaterDisplay(1);
}