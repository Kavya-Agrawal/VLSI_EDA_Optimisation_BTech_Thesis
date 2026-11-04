// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23670766;
  double density_weight = 0.46277829;
  double prefix_weight = 0.28948714;
  double neighborhood_weight = 0.27747362;
  double late_weight = 0.09547723;
  double critical_weight = 0.02052655;
  unsigned budget = 34;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
