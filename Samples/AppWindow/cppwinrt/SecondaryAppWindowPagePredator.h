//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

#pragma once

#include "SecondaryAppWindowPagePredator.g.h"
#include "ecoinMain.h"

#define ECOIN_COM_WILDCARD_SW '\%%s\%'

extern winrt::Windows::UI::WindowManagement::AppWindow appWindowPredator;
extern winrt::Windows::UI::Xaml::Controls::TextBox appWindowPredatorTextBox;

namespace winrt::SDKTemplate::implementation
{
    struct SecondaryAppWindowPagePredator : SecondaryAppWindowPagePredatorT<SecondaryAppWindowPagePredator>
    {
	public:
        SecondaryAppWindowPagePredator();

        void OnVisibilityChanged(winrt::AppWindow sender, winrt::VisibilityChangedEventArgs args);
		void OnSizeChanged(winrt::AppWindow sender, winrt::AppWindowChangedEventArgs args);
		void SizeChanged(winrt::Windows::Foundation::Size f_size);

#if 0
        void SaveInternalState(Windows::Foundation::Collections::IPropertySet state);
        void LoadInternalState(Windows::Foundation::Collections::IPropertySet state);
#endif

        // XAML low-level rendering event handler.
		void OnRendering(IInspectable sender, IInspectable args);

		event_token visibilityToken;

		std::string ac_AB(std::string f_StringIn, int f_CursorPosition);

#if 0 // Resources used to render the DirectX content in the XAML page background.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;
#endif

		void OnClickWindow(IInspectable sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs e);
		void OnReleaseWindow(IInspectable sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs e);
		void OnRightClickWindow(IInspectable sender, Windows::UI::Xaml::Input::RightTappedRoutedEventArgs e);
	
		void acBuild_ExcomPackaging(void);
		void OnClickComFunction(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);

		bool m_windowVisible;
	
		void acLoadShare(int f_LShare = 0, int f_ServLay = 0);

		void OnPrintCopyStackPage(void);
		void OnCreateNewCopyStackPage(void);

		winrt::Windows::Graphics::Display::DisplayOrientations	m_nativeOrientation;
		winrt::Windows::Graphics::Display::DisplayOrientations	m_currentOrientation;

		int ConvertDipsToPixels(float dips);
		float ConvertPixelsToDips(int pixels);

		DXGI_MODE_ROTATION ComputeDisplayRotation(void);

		std::byte HexToByteUsingByteManipulation(std::string s);

		double atodi(std::string f_String);

		void acClick(std::string f_ButtonName);

		void OnClickCopyStack11(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickCopyStack12(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickCopyStack13(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickCopyStack21(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickCopyStack22(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickCopyStack23(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickCopyStack31(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickCopyStack32(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickCopyStack33(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickCopyStack41(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickCopyStack42(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickCopyStack43(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickCopyStackPrevPage(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickCopyStackCommandPrev(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickCopyStackCommandNext(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickCopyStackNextPage(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickCopyStackClear(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickSaveComplete(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickSave(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickSaveAll(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnHoverPredatorMain(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

		winrt::Windows::UI::Xaml::Controls::Frame appWindowFrame{};

	protected:
		float	m_DPI;
		float	m_logicalWidth;
		float	m_logicalHeight;
		float	m_outputWidth;
		float	m_outputHeight;
	};
}

namespace winrt::SDKTemplate::factory_implementation
{
    struct SecondaryAppWindowPagePredator : SecondaryAppWindowPagePredatorT<SecondaryAppWindowPagePredator, implementation::SecondaryAppWindowPagePredator>
    {
    };
}