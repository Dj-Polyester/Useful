\ProvidesClass{props}[2020/03/08 script class]
\NeedsTeXFormat{LaTeX2e}

\DeclareOption*{%
  \PassOptionsToClass{\CurrentOption}{article}%
}
\ProcessOptions\relax
\LoadClass{article}

\makeatletter

%%%%%%%%%%
% Colors %
%%%%%%%%%%

\RequirePackage{xcolor}

\definecolor{white}{RGB}{255,255,255}

\definecolor{darkgray}{HTML}{333333}
\definecolor{gray}{HTML}{4D4D4D}
\definecolor{lightgray}{HTML}{999999}

\definecolor{green}{HTML}{C2E15F}
\definecolor{orange}{HTML}{FDA333}
\definecolor{purple}{HTML}{D3A4F9}
\definecolor{red}{HTML}{FB4485}
\definecolor{blue}{HTML}{6CE0F1}

\colorlet{fillheader}{white}
\colorlet{header}{gray}
\colorlet{textcolor}{gray}
\colorlet{headercolor}{gray}
\colorlet{fillPanel}{white}

%%%%%%%%%
% Fonts %
%%%%%%%%%

\RequirePackage[quiet]{fontspec}
\RequirePackage[math-style=TeX]{unicode-math}

\newfontfamily\bodyfont
[BoldFont=texgyreheros-bold.otf,
ItalicFont=texgyreheros-italic.otf,
BoldItalicFont=texgyreheros-bolditalic.otf]
{texgyreheros-regular.otf}
\newfontfamily\thinfont[]{Lato-Light.ttf}
\newfontfamily\headingfont[]{texgyreheros-bold.otf}

\defaultfontfeatures{Mapping=tex-text}
\setmainfont
[Mapping=tex-text, Color=textcolor,
BoldFont=texgyreheros-bold.otf,
ItalicFont=texgyreheros-italic.otf,
BoldItalicFont=texgyreheros-bolditalic.otf
]
{texgyreheros-regular.otf}

%%%%%%%%%%
% Header %
%%%%%%%%%%


\RequirePackage{tikz}

% \newcommand{\rolefont}{%
%   \fontsize{14pt}{24pt}\selectfont%
%   \thinfont%
%   \color{white}%
% }



%%%%%%%%%%%%%
% Structure %
%%%%%%%%%%%%%
%hlines
\newcommand{\widthline}{\noindent\makebox[\linewidth]{\rule{\paperwidth}{0.2pt}}} 
%Header
\newcommand{\header}[2]{%
  \begin{tikzpicture}[remember picture,overlay]
    \node [rectangle, thick, fill=fillheader, anchor=north,minimum width = \paperwidth, minimum height=3cm] (box) at (current page.north){};
    \node [anchor=west, xshift=2.8cm] (name) at (box.west) {%
      \fontsize{30pt}{60pt}\color{header}%
      {\thinfont #1}{\bodyfont  #2}
    };
    % \node [anchor=north] at (name.south) {%
    %   \fontsize{14pt}{24pt}\color{header}%
    %   \thinfont #3%
    % };
  \end{tikzpicture}
  \vspace{2.5cm}
  \vspace{-2\parskip}
}
%Panel
\newcommand{\panel}[2]{
  \begin{tikzpicture}[remember picture,overlay]
    
    \node [rectangle, fill=white, anchor=#1, xshift=-5.0mm, yshift=-5.0mm ] (box) at (current page.#1){
        \begin{tabular}{l}
            #2
        \end{tabular}
    };
  \end{tikzpicture}
}

\RequirePackage{parskip}

\newcounter{colorCounter}
\def\@sectioncolor#1#2#3{%
  {%
    \color{%
      \ifcase\value{colorCounter}%
        blue\or%
        red\or%
        orange\or%
        green\or%
        purple\else%
        headercolor\fi%
    } #1#2#3%
  }%
  \stepcounter{colorCounter}%
}

\renewcommand{\section}[1]{
  \par\vspace{\parskip}
  {%
    \LARGE\headingfont\color{headercolor} #1%
    
  }
  \widthline
  \par\vspace{0\parskip}
}
\renewcommand{\subsection}[1]{
  \par\vspace{0\parskip}
  {%
    \large\headingfont\color{headercolor} #1%
   
  }
  \par\vspace{\parskip}
}

\pagestyle{empty}