// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12644248;
  double density_weight = 0.23902474;
  double prefix_weight = 0.49975989;
  double neighborhood_weight = 0.22732429;
  double late_weight = 0.13617378;
  double critical_weight = 0.10629114;
  unsigned budget = 24;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
