#include "file_types_items.h"

unsigned long long gdi_token;

void file_collector::start() 
{
  Gdiplus::GdiplusStartupInput startup_input;
  ::Gdiplus::GdiplusStartup(&::gdi_token, &startup_input, NULL);
}

void file_collector::redraw() 
{
  
} 

void file_collector::stop() 
{
  ::Gdiplus::GdiplusShutdown(::gdi_token);
}

void file_collector::add_item(item_list &Item_list, item Item)
{
  Item_list.item_vector.push_back(Item);
  Item_list.pending_change = true;
}


void file_collector::delete_item(item_list& Item_list, int index)
{
  for (size_t iterator = index+1; iterator < Item_list.item_vector.size(); iterator++)
  {
    Item_list.item_vector[iterator - 1] = Item_list.item_vector[iterator];
  }
  Item_list.item_vector.pop_back();
}

int file_collector::find_item_by_position(item_list& Item_list, click_range &Click_range, float x, float y)
{
  int iterator = 0;
  return item_search(Item_list, Click_range, x, y, iterator);
}

int item_search(file_collector::item_list &Item_list, file_collector::click_range &Click_Range, float x, float y, int i) 
{
  if (i >= Item_list.item_vector.size())
  {
    return -1;
  }
  if (click_in_bounds(Item_list.item_vector[i].x, Item_list.item_vector[i].y, x, y, Click_Range))
  {
    OutputDebugString(L" Yeah ");
    return i;
  }
  else
  {
    OutputDebugString(L" - ");
    return item_search(Item_list, Click_Range, x, y, i+1);
  }
}

bool click_in_bounds(float x, float y, float click_x, float click_y, file_collector::click_range Click_range)
{
  return click_x > x - Click_range.x && 
    click_x < x + Click_range.x && 
    click_y > y - Click_range.y && 
    click_y < y + Click_range.y;
}

void file_collector::draw_button(int window_size_x, int window_size_y, HDC hdc, item_list& list)
{
  Gdiplus::Graphics graphics(hdc);
  Gdiplus::Pen pen(Gdiplus::Color(255,255,0,0));
  Gdiplus::SolidBrush  brush(Gdiplus::Color(255, 0, 0, 255));
  Gdiplus::FontFamily  fontFamily(L"Times New Roman");
  Gdiplus::Font        font(&fontFamily, 14, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
  for (size_t i = 0; i < list.item_vector.size(); i++)
  {
    graphics.DrawRectangle(&pen, Gdiplus::Rect(int(float(window_size_x)*list.item_vector[i].x) -50, int(float(window_size_y) * list.item_vector[i].y) -15, 100, 30));
    graphics.DrawString(&list.item_vector[i].file_path.front(), -1, &font, Gdiplus::PointF(float(window_size_x) * list.item_vector[i].x - 50.0f, float(window_size_y) * list.item_vector[i].y - 15.0f), &brush);
  }
}
