window.onload = function() {
    const selectedValue = localStorage.getItem('selectedValue');
    const selectedValue1 = localStorage.getItem('selectedValue1');
    const selectedValue2 = localStorage.getItem('selectedValue2');
    const selectedValue3 = localStorage.getItem('selectedValue3');
    const selectedValue4 = localStorage.getItem('selectedValue4');
    if(selectedValue) {
        document.getElementById('code').value = selectedValue;
        document.getElementById('nom').value = selectedValue1;
        document.getElementById('tel').value = selectedValue2;
        document.getElementById('ville').value = selectedValue3;
        document.getElementById('adresse').value = selectedValue4;
    }
}



