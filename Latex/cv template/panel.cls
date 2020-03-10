\ProvidesClass{panel}[2020/03/02 script class]
\NeedsTeXFormat{LaTeX2e}

%\DeclareOption{print}{\def\@cv@print{}}
\DeclareOption*{%
  \PassOptionsToClass{\CurrentOption}{article}%
}
\ProcessOptions\relax
\LoadClass{article}

\makeatletter
\newcommand{\fillPanelColor}{white}
%Colors
\RequirePackage{xcolor}
\definecolor{gray}{HTML}{4D4D4D}

\ifdefined\@cv@print
  \colorlet{fillPanel}{white}
\else
  \colorlet{fillPanel}{\fillPanelColor}




%Calculate height of the panel

%\FPeval{\panelHeight}{clip(\ItemCount+2)}


\RequirePackage{fp}
\RequirePackage{tikz}

\newcommand{\setPanel}[3]{
  \FPeval{\panelHeight}{clip(#3+2)}
  \begin{tikzpicture}[remember picture,overlay]
    
    \node [rectangle, fill=fillPanel, anchor=#1, minimum width=10cm, minimum height=\panelHeight cm] (box) at (current page.#1){};
   
    \foreach[count=\i, evaluate=\i as \x using int((-\i)*10)] \Item in #2 {
        \node[transform canvas = {xshift=10mm,yshift=\x mm}, anchor = north west] at (box.north west) {
        \Item 
        };
    }
    
  \end{tikzpicture}
}

%draw=blue!80, thick,
%add above between nodes brackets to add blue border lines to the panel

