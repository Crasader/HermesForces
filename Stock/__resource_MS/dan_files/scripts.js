$(function() {
    // Link Targets
    $('a[href][rel=external]').attr('target', '_blank');
    // Image Title Attributes
    $('img').each(function() {
        $(this).attr('title', $(this).attr('alt'));
    });
    // Disable Submit Buttons
    $('form').submit(function() {
        $('input[type=submit][name!="more"][name!="cancel"]', this).prop('disabled', true);
    });
    // Code Reference
    $('input[value="Code Reference"]').click(function() {
        window.open('/coderef.php', 'coderef', 'width=630,height=787,status=0,toolbar=0,location=0,menubar=0,directories=0,resizable=0,scrollbars=0');
    });
    // Share Buttons
    $('.share').click(function() {
        window.open($(this).attr('href'), 'share', 'width=860,height=500,status=0,toolbar=0,location=0,menubar=0,directories=0,resizable=0,scrollbars=0');
        return false;
    });
    // Spoilers
    $('.spoiler').hover(function() {
        $(this).find('.spoiler-text').css('background-color', '#ffffff');
    }, function() {
        $(this).find('.spoiler-text').css('background-color', '#000000');
    });
    // Toggle Other Systems
    $('#toggle_other').click(function() {
        if($('#other').is(':visible')) {
            $('#other').slideUp('fast');
            $(this).attr('src', '/images/buttons/nav-closed.png');
            return false;            
        } else {
            $('#other').slideDown('fast');
            $(this).attr('src', '/images/buttons/nav-open.png');
            return false;
        }
    });
    // Toggle Navigation Menu
    $('.nav-header').click(function() {
        var selected = 'left' + $(this).attr('id').split('_')[0];
        if($('#' + selected).is(':visible')) {
           $('#' + selected).slideUp('fast');
           $('#' + selected + '-arrow').attr('src', '/images/buttons/nav-closed.png');
        } else {
           $('#' + selected).slideDown('fast');
           $('#' + selected + '-arrow').attr('src', '/images/buttons/nav-open.png');
           $('div[id^="leftnav-"][id!="' + selected +'"]').each(function() {
               if($(this).is(':visible')) {
                   $(this).slideUp('fast');
                   $('#' + $(this).attr('id') + '-arrow').attr('src', '/images/buttons/nav-closed.png');
               }
           });
        }
    });
    // Header Resize on Scroll
    $(document).scroll(function() {
        if($(window).width() > 766 && $(window).height() > 800 && window.location.pathname.indexOf('fullview') < 0) {
            if(typeof window.av_width == 'undefined' || typeof window.av_height == 'undefined') {
                window.av_width = [];
                window.av_height = [];
                window.av_width['large'] = $('#userbox img').width();
                window.av_height['large'] = $('#userbox img').height();
                if(window.av_width['large'] > window.av_height['large']) {
                    window.av_width['small'] = 40;
                    window.av_height['small'] = Math.round(40 / (window.av_width['large'] / window.av_height['large']));
                } else {
                    window.av_width['small'] = Math.round(40 / (window.av_height['large'] / window.av_width['large']));
                    window.av_height['small'] = 40;
                }
            }
            if($(this).scrollTop() > 130) {
                $('#header img:first').attr('src', '/resources/images/header/logo-small.png');
                $('#userbox img').width(window.av_width['small']).height(window.av_height['small']);
                if($('#userbox div:eq(1):contains("Register today")').length > 0) {
                    $('#userbox div:eq(1)').text('Register today to access all features of the site!');
                } else {
                    $('.small-hide').css('display', 'none');
                }
                $('#header').addClass('small');
                $('#userbox').addClass('small');
                $('#search').addClass('small');
                $('#nav-top').addClass('small');
                $('#userbox.small img').parent().css('width', '40px').css('height', '40px');
                $('#skinleft').css('top', '80px');
                $('#skinright').css('top', '80px');
            } else {
                $('#skinright').css('top', '129px');
                $('#skinleft').css('top', '129px');
                $('#nav-top').removeClass('small');
                $('#search').removeClass('small');
                $('#userbox').removeClass('small');
                $('#header').removeClass('small');
                if($('#userbox div:eq(1):contains("Register today")').length > 0) {
                    $('#userbox div:eq(1)').text('Register today to join in with discussions on the forum, post comments on the site, and upload your own sheets!');
                } else {
                    $('.small-hide').css('display', 'inline-block');
                }
                $('#userbox img').parent().css('width', '74px').css('height', '74px');
                $('#userbox img').width(window.av_width['large']).height(window.av_height['large']);
                $('#header img:first').attr('src', '/resources/images/header/logo.png');
            }
        }
    });
    // Resize comment images and videos
    $('.commentContent img, #commentList img, #commentList iframe').each(function() {
        var maxWidth = ($(this).parents('#commentList').length > 0 ? 200 : 700);
        $(this).load(function() {
            if($(this).width() > maxWidth) {
                $(this).width(maxWidth);
                $(this).height(Math.round(maxWidth / ($(this).attr('width') / $(this).attr('height'))));
                if($(this).is('img')) {
                    $(this).css('cursor', 'pointer');
                    $(this).click(function() {
                        window.open($(this).attr('src'), '_blank');
                    });
                }
            }
        });
    });
    // Unhide NSFW Content
    $('.nsfw-warning').click(function() {
        $(this).slideUp('fast');
        $('.nsfw').slideDown('fast');
    });
    // Update Sheet Display Toggle
    $('#toggle-link, #include-sheets').click(function() {
        var word = '';
        switch(location.host) {
            case "www.models-resource.com":
                word = "Models";
                break;
            case "www.sounds-resource.com":
                word = "Sounds";
                break;
            case "www.spriters-resource.com":
                word = "Sheets";
                break;
            case "www.textures-resource.com":
                word = "Textures";
                break;
        }
        // Toggle Sheets on Add Update Page
        if($(this).attr('id') == 'include-sheets') {
            if($(this).is(':checked')) {
                $('#sheets_msg').html('Uncheck to post this update without ' + word.toLowerCase());
            } else {
                $('#sheets_msg').html('Check to include ' + word.toLowerCase() + ' with this update');
            }            
        }
        if($('#updatesheets').is(':visible')) {
            $('#updatesheets').slideUp('slow');
            $(this).html('Show ' + word);
        } else {
            $('#updatesheets').slideDown('slow');
            $(this).html('Hide ' + word);
        }
        return $(this).attr('id') == 'include-sheets';
    });
    // Submitter Profile Console Toggle
    $('[id$="-console-link"]').click(function() {
        var id = $(this).attr('id').split('-')[0];
        if($('#' + id + '-list td').is(':visible')) {
            $('#' + id + '-list td').css('display', 'none');
            $(this).html('Show');
        } else {
            $('#' + id + '-list td').css('display', 'table-cell');
            $(this).html('Hide');
        }
        return false;
    });
    // Edit Section Form
    $('.edit-section').click(function() {
        if(typeof window.original == 'undefined') {
            window.original = [];
        }
        var id = $(this).attr('id').split('-')[1];
        window.original[id] = $(this).siblings('div.sect-name').text();
        $(this).siblings('div.sect-name').html('<input type="text" name="sect[' + id + ']" id="sect-' + id + '-form" size="40" class="formElement" value="' + $.trim($(this).parent().text()) + '" />');
        $(this).css('display', 'none');
        if(!$('#section-form-buttons').is(':visible')) {
            $('#section-form-buttons').css('display', 'block');
        }
    });
    $('#cancel_sections').click(function() {
        $('#section-form-buttons').css('display', 'none');
        $('input[name^="sect"]').each(function() {
            $(this).parent().siblings('img.edit-section').css('display', 'initial');
            $(this).parent().html(window.original[$(this).attr('id').split('-')[1]]);
        });
    });
    // Temporary iframe Fix
    $('iframe[src$="safari.html"]').css('display', 'none');
    // Confirm Delete
    $('#delete').change(function() {
        var form = $(this).parents('form:first');
        form.submit(function() {
            if($('#delete').is(':checked')) {
                if(confirm('You have marked this item for deletion. If you are sure, click OK. Otherwise, click Cancel.')) {
                    return true;
                } else {
                    form.find('input[type="submit"]').removeProp('disabled');
                    return false;
                }
            } else {
                return true;
            }
        });
    });
    // Toggle New Section Field
    $('#sect, #console').change(function() {
        if($(this).val() == 'new') {
            $('#new-sect').css('display', 'inline');
        } else {
            $('#new-sect').css('display', 'none');
        }
    });
    // Auto-Fill Sheet Name from File Name
    $('#sheet-up').change(function() {
        if($('#name').val() == '') {
            var file = $(this).val();
            var index1 = file.lastIndexOf('\\');
            var index2 = file.lastIndexOf('.');
            var name = file.substring(index1 + 1, index2)
            $('#name').val(name);
        }
    });
    // Auto-Select Radio Buttons and Checkboxes on Forms
    $('input[type!="radio"][type!="checkbox"]').change(function() {
        if($(this).prevAll('input[type="radio"], input[type="checkbox"]').length) {
            if($(this).val() != '') {
                $(this).prevAll('input[type="radio"]:first, input[type="checkbox"]:first').prop('checked', true);
                $(this).prevAll('input[type="radio"]:first, input[type="checkbox"]:first').trigger('change');
            } else {
                $(this).prevAll('input[type="checkbox"]:first').removeProp('checked');
                $(this).prevAll('input[type="checkbox"]:first').trigger('change');
            }
        }
    });
    // Toggle Reject Form
    $('[id^="reject-"]').click(function () {
        var id = $(this).attr('id').split('-')[1];
        if($('#reject_' + id).is(':visible')) {
            $(this).html('REJECT');
            $('#reject_' + id).fadeOut('slow');
        } else {
            $(this).html('CANCEL');
            $('#reject_' + id).fadeIn('slow');
        }
        return false;
    });
    // Confirm Rejections
    $('input[value="Reject"]').click(function() {
        if(confirm('You are about to reject this item. This action cannot be undone. Click OK to continue or Cancel to go back.')) {
            return true;
        } else {
            $(this).removeProp('disabled');
            return false;
        }
    });
    // Confirm Cancellation
    $('.cancel').click(function() {
        return confirm('You are about to cancel this item, permanently removing it from the queue. This action cannot be undone. Click OK to continue or Cancel to go back.');
    });
    // Toggle Update Checkbox on Edit Pages
    $('input[type="radio"][name="stype"]').change(function() {
        if($('#update-row').length) {
            if($(this).val() != 'keep') {
                $('#update-row').fadeIn('slow');
            } else {
                $('#update-row').fadeOut('slow');
            }
        }
    });
    // Toggle Selected Game Status Field
    $('select[id="game"]').change(function() {
        var label = $('#game :selected').parent().attr('label');
        if(label == 'Pending Games') {
            $('#sel_game_status').val('0');
        } else {
            $('#sel_game_status').val('1');
        }
    });
    // Toggle Preserve Shortname Checkbox
    $('#edit_game_name').on('input propertychange paste', function() {
        if($('#game_status').val() == 1 && $('#console').val() == window.console_id) {
            if($(this).val() != window.game_name) {
                $('#preserve_box').fadeIn('slow');
            } else {
                $('#preserve_box').fadeOut('slow');
            }
        }
    });
});