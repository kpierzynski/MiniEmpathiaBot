import { useState } from "react";

import Video from "./components/Video";
import NewFeed from "./components/NewFeed";

function App() {
	const [videoCount, setVideoCount] = useState(1);

	return (
		<div className="bg-gray-200 min-h-screen">
			<div className="container mx-auto gap-2 flex flex-col p-2">
				<div className={`grid gap-2 auto-rows-fr grid-cols-1 sm:grid-cols-2`}>
					{videoCount ? (
						Array.from({ length: videoCount }).map((_, i) => (
							<Video key={`video-feed-${i}`} />
						))
					) : (
						<p className="text-gray-500 text-center">No streams</p>
					)}
					<NewFeed onClick={() => setVideoCount(videoCount + 1)} />
				</div>
			</div>
		</div>
	);
}

export default App;
