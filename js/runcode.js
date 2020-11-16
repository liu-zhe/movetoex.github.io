document.addEventListener('DOMContentLoaded', () => {
    var items = document.querySelectorAll('.runcode-button');
    for (var i = 0; i < items.length; ++i) {
        var fn = items[i].getAttribute('file');
        items[i].innerHTML = '<i class="fa fa-code"></i>' + fn;
        items[i].addEventListener('click', (e) => {
            window.open('/run-code/?' + e.target.getAttribute('file'));
        });
    }
});