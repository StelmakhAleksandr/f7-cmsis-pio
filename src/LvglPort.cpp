#include "LvglPort.h"

LvglPort::LvglPort(const stmcmp::LcdConfig& config)
    : m_config(config)
{
}

void LvglPort::setup()
{
    lv_init();
    setupDisplayDriver();
    setupTouchDriver();
}

typedef struct
{
    lv_draw_unit_t base_unit;
    lv_draw_task_t* task_act;
    uint32_t idx;
} lv_draw_my_unit_t;

void LvglPort::setupDisplayDriver()
{
    lv_display_t* display = lv_display_create(m_config.activeWidth, m_config.activeHeight);
    stmcmp::Dma2d dma2d;
    dma2d.setup();
    lv_display_set_flush_cb(display, [](lv_display_t* display, const lv_area_t* area, uint8_t* px_map) {
        // auto buf = stmcmp::Lcd::instance()->workBuffer(0);
        // uint32_t destOffset = ((area->y1) * 480 + area->x1) * 4;
        // uint32_t width = lv_area_get_width(area);
        // uint32_t height = lv_area_get_height(area);
        // uint32_t oor = 480 - width;
        // static stmcmp::Dma2d dma2d;
        // dma2d.copyMemToMemRegion((uint32_t)px_map, (uint32_t)buf + destOffset, width, height, oor);
        stmcmp::Lcd::instance()->swapBuffers(0);
        lv_display_flush_ready(display);
    });

    // static std::vector<uint32_t, stmcmp::SdramAllocator<uint32_t>> buf(m_config.activeHeight * m_config.activeWidth / 10);
    // lv_display_set_buffers(display, &buf.at(0), NULL, buf.size() * 3, LV_DISPLAY_RENDER_MODE_PARTIAL);
    auto lcd = stmcmp::Lcd::instance();
    auto buf1 = lcd->workBuffer(0);
    lcd->swapBuffers(0);
    auto buf2 = lcd->workBuffer(0);

    lv_display_set_color_format(display, LV_COLOR_FORMAT_ARGB8888);
    lv_display_set_buffers(display, buf1, buf2, m_config.activeWidth * m_config.activeHeight * 4, LV_DISPLAY_RENDER_MODE_FULL);

    // lv_display_add_event_cb(
    //     display, [](lv_event_t* e) {
    //         stmcmp::Lcd::instance()->swapBuffers(0);
    //     },
    //     LV_EVENT_REFR_READY,
    //     nullptr);

    lv_tick_set_cb([](void) {
        return stmcmp::SystemClock::millisecondsElapsed();
    });
}

void LvglPort::setupTouchDriver()
{
    lv_indev_t* indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, [](lv_indev_t* indev, lv_indev_data_t* data) {
        auto touch = stmcmp::Touch::instance();
        if (touch->hasTouch()) {
            auto touchState = touch->lastTouch();
            data->point.x = touchState.x;
            data->point.y = touchState.y;
            data->continue_reading = touch->hasTouch();
            data->state = LV_INDEV_STATE_PRESSED;
        } else {
            data->state = LV_INDEV_STATE_RELEASED;
        }
    });
}
