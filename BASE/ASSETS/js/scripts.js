document.addEventListener('DOMContentLoaded', () => {
    const table = document.getElementById('dataTable');
    
    table.addEventListener('click', (event) => {
    let target = event.target;
    while (target && target.nodeName !== 'TR') {
    target = target.parentElement;
    }
    
    if (!target || target.nodeName !== 'TR' || target === table.rows[0]) {
     return;
    }
    // Clear previous selection
    const selectedRow = table.querySelector('tr.selected');
    if (selectedRow) {
    selectedRow.classList.remove('selected');
    }
    
    // Mark the clicked row as selected
    target.classList.add('selected');
    
    // Get the data from the selected row
    const cells = target.getElementsByTagName('td');
    if (cells.length > 0) {

        function selectValue(value, value1, value2, value3, value4) {
            localStorage.setItem('selectedValue', value);
            localStorage.setItem('selectedValue1', value1);
            localStorage.setItem('selectedValue2', value2);
            localStorage.setItem('selectedValue3', value3);
            localStorage.setItem('selectedValue4', value4);
            window.location.href = 'main.exe';
        }

        selectValue(cells[0].textContent, cells[1].textContent, cells[2].textContent, cells[3].textContent, cells[4].textContent);
     }
    });
    });